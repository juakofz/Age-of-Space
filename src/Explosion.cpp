#include "Explosion.h"

//Static variables
Texture * Explosion::m_tex = 0;
float Explosion::scale = 2;


Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

Explosion::Explosion(int x, int y, int size)
{
	Vector2 v(x, y);
	* this = Explosion(v, size);
}

Explosion::Explosion(Vector2 cen, int size)
{
	//Set explosion center
	m_cen = cen;

	m_number = size * scale * 2; //Projectile number

	//Create projectiles
	Projectile * proy = new Projectile[m_number];
	for (int i = 0; i < m_number; i++)
	{
		proy[i].setTex(m_tex);
		proy[i].scaleTo(10);
		m_tex->setColor(g_rand_solidcolor()); //Random explosion color!

		proy[i].setCen(cen);
		proy[i].setSpeed(3 + g_rand_float(-1.0, 1.0));

		float angle = (360 / m_number) * i + (rand() % 11 - 5); //Slightly random angle
		proy[i].setAngle(angle);

		//Destination
		float reach = size * 0.5 * ((rand() % 100) / 5 + 1);
		float dest_x = m_cen.x + proy[i].getDir().x * reach;
		float dest_y = m_cen.y + proy[i].getDir().y * reach;
		proy[i].setDest(dest_x, dest_y);

		//Velocity
		Vector2 vel = proy[i].getDest() - cen;
		vel = vel.normalize(proy[i].getSpeed());
		proy[i].setVel(vel);

		v_projectiles.add(&proy[i]); //Add to object vector
	}
}

void Explosion::update()
{
	if (v_projectiles.count() > 0) //If there are still projectiles left
			v_projectiles.move();
}

bool Explosion::render(Camera cam)
{
	update();
	if (v_projectiles.count() > 0)
		v_projectiles.render(cam);
	return false;
}

void Explosion::setTexture(Texture * t)
{
	m_tex = t;
}
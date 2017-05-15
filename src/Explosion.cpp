#include "Explosion.h"

//Static variables
Texture * Explosion::m_tex = 0;
float Explosion::scale = 0.6;


Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

Explosion::Explosion(int x, int y, int size)
{
	m_cen.x = x;
	m_cen.y = y;

	m_number = size * scale; //Projectile number

	//Create projectiles
	Projectile * proy = new Projectile[m_number];
	for (int i = 0; i < m_number; i++)
	{

		proy[i].setTex(m_tex);
		proy[i].scaleTo(10);
		m_tex->setColor(rand()%255, rand() % 255, rand() % 255); //Random color!
		
		proy[i].setCen(x, y);
		proy[i].setSpeed(3);

		float angle = (360 / m_number) * i + (rand() % 11 - 5); //Slightly random angle
		proy[i].setAngle(angle);

		//Destination
		float reach = size * 0.05 * ((rand() % 100) / 5);
		float dest_x = m_cen.x + proy[i].getDir().x * reach;
		float dest_y = m_cen.y + proy[i].getDir().y * reach;
		proy[i].setDest(dest_x, dest_y);

		v_projectiles.add(&proy[i]); //Add to object vector
	}
}

void Explosion::update()
{
	v_projectiles.move();
}

bool Explosion::render(Camera cam)
{
	update();
	return false;
}

void Explosion::setTexture(Texture * t)
{
	m_tex = t;
}
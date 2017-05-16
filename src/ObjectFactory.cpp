#include "ObjectFactory.h"



ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

Explosion * ObjectFactory::createExplosion(Vector2 cen, int size)
{
	Explosion * aux = new Explosion(cen, size);
	return aux;
}

Projectile * ObjectFactory::createExplosionProjectile(Vector2 cen, int size, int number, int i)
{
	Projectile * aux_proj = new Projectile;
	
	//Texture
	Texture * aux_tex = g_tex + 10;
	aux_tex->setColor(g_rand_solidcolor()); //Random color!
	aux_proj->setTex(aux_tex);
	aux_proj->scaleTo(10);
	
	//Placement
	aux_proj->setCen(cen);
	aux_proj->setSpeed(3 + g_rand_float(-1.0, 1.0));
	float angle = (360 / number) * i + (g_rand_float(-5.0f, 5.0f)); //Slightly random angle
	aux_proj->setAngle(angle);

	//Destination
	float reach = size * 0.5 * ((rand() % 100) / 5 + 1);
	float dest_x = cen.x + aux_proj->getDir().x * reach;
	float dest_y = cen.y + aux_proj->getDir().y * reach;
	aux_proj->setDest(dest_x, dest_y);

	//Velocity
	Vector2 vel = aux_proj->getDest() - cen;
	vel = vel.normalize(aux_proj->getSpeed());
	aux_proj->setVel(vel);

	return aux_proj;
}
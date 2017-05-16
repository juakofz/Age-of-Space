#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Explosion.h"


class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	static Explosion * createExplosion(Vector2 cen, int size);

	static Projectile * createExplosionProjectile(Vector2 cen, int size, int number, int i);

	
};


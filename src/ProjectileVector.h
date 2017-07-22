#pragma once
#include "T_Vector.h"
#include "Projectile.h"

class ProjectileVector: public T_Vector<Projectile>
{
public:

	Vector2 getCen(int i);
	float getSize(int i);
	int getPlayer(int i);

	void move();
	void render(Camera cam);

};
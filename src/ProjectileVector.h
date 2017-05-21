#pragma once
#include <vector>
#include "Projectile.h"

class ProjectileVector
{
public:
	ProjectileVector();
	~ProjectileVector();

	bool in(int i);

	void add(Projectile * projectile);
	void erase(int i);
	int count();
	Projectile * get(int i);

	Vector2 getCen(int i);
	float getSize(int i);

	void move();
	void render(Camera cam);

	
protected:
	vector<Projectile * > v_projectile;
};
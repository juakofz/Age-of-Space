#pragma once
#include "ProjectileVector.h"
#include "Projectile.h"
#include <cstdlib>
#include <vector>


class Explosion
{
public:
	Explosion();
	Explosion(int x, int y, int size);
	Explosion(Vector2 cen, int size);
	~Explosion();

	vector<Vector2> v_directions;

private:

	Vector2 m_cen;

	const float m_scale = 1.0f;
	int m_number;

	
};


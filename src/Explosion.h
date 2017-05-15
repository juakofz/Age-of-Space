#pragma once

#include "MovingObjectVector.h"
#include "Projectile.h"
#include <cstdlib>

class Explosion
{
public:
	Explosion();
	Explosion(int x, int y, int size);
	Explosion(Vector2 cen, int size);
	~Explosion();

	void update();
	bool render(Camera cam);
	
	static void setTexture(Texture *t);

private:
	static Texture * m_tex;
	int m_size;
	int m_number;

	static float scale;

	MovingObjectVector v_projectiles;
	Vector2 m_cen;
};


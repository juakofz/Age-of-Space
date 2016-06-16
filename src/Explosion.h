#pragma once

#include "Vector2.h"
#include "ListaProyectiles.h"
#include <cstdlib>

class Explosion
{
public:
	Explosion();
	Explosion(int x, int y, int size);
	~Explosion();

	bool render(Camera cam);
	
	static void setTexture(Texture *t);

private:
	static Texture *tex;
	int size;

	static float scale;

	ListaProyectiles l_proy;
	Vector2 pos;
};


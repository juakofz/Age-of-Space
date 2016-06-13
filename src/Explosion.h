#pragma once

#include "Vector2.h"
#include "ListaProyectiles.h"
#include <cstdlib>

class Explosion
{
public:
	Explosion();

	Explosion(int x, int y, int size);

	bool render(Camera cam);
	
	static void setTexture(Texture *t);

private:
	static Texture *tex;
	int size;
	const int scale = 5;
	ListaProyectiles l_proy;
	Vector2 pos;
};


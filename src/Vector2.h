#pragma once
#include <SDL.h>

class Vector2
{


public:

	//Constructor
	Vector2(float px = 0, float py = 0);
	
	//Destructor
	~Vector2();

	//Coordenadas
	float x, y;

	//PAsar a int
	SDL_Point convert_int();

	float modulo();
	float argumento();
	//void norm(int l);
	Vector2 operator-(Vector2 v);
};


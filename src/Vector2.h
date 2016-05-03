#pragma once
#include <SDL.h>

class Vector2
{
public:

	//Constructor
	Vector2(float px=0, float py=0);
	
	//Destructor
	~Vector2();

	//PAsar a int
	SDL_Point convert_int();

	//Coordenadas
	float x, y;
};


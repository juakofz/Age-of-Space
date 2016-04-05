#include "Vector2.h"


//Constructor
Vector2::Vector2()
{
	//Valor por defecto
	x = y = 0.f;
}

//Destructor
Vector2::~Vector2()
{
}

//SDL_Point

SDL_Point Vector2::convert_int()
{
	SDL_Point ret;
	ret.x = x;
	ret.y = y;

	return ret;
}
#include "Vector2.h"


//Constructor
Vector2::Vector2(float px, float py)
{
	x=px;
	y=py;
}

//Destructor
Vector2::~Vector2()
{
}

SDL_Point Vector2::convert_int()
{
	SDL_Point ret;
	ret.x = x;
	ret.y = y;

	return ret;
}
#include "Vector2.h"
#include <math.h>

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

float Vector2::modulo()
{
	return sqrt(x*x + y*y);
}

float Vector2::argumento()
{
	return (180 * atan2(y, x) / M_PI);
}

Vector2 Vector2::operator-(Vector2 v)
{
	return Vector2(x-v.x, y-v.y);
}
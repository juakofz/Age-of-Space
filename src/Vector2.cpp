#include "Vector2.h"
#include <math.h>

//Constructor
Vector2::Vector2(float px, float py)
{
	x = px;
	y = py;
}

Vector2::Vector2(SDL_Point p)
{
	x = static_cast<float>(p.x);
	y = static_cast<float>(p.y);
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
	return sqrt(x * x + y * y);
}

float Vector2::argumento()
{
	float aux;
	aux = 180 * atan2(y, x) / M_PI;
	if (aux<0) return (aux + 360);
	else return aux;
	//return (180 * atan2(y, x) / M_PI);
}

Vector2 Vector2::operator + (Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (Vector2 v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator = (Vector2 v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator += (Vector2 v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator -= (Vector2 v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator = (SDL_Point p)
{
	x = static_cast<float>(p.x);
	y = static_cast<float>(p.y);
	return(Vector2(x, y));
}

Vector2 Vector2::operator * (float k)
{
	return Vector2(k*x, k*y);
}

float Vector2::distancia(Vector2 dest)
{
	//Vector2 aux = *this - dest;
	Vector2 aux = dest - *this;
	return aux.modulo();
}

Vector2 Vector2::norm(float n)
{
	Vector2 aux;
	aux.x = n * x / modulo();
	aux.y = n * y / modulo();
	return aux;
}

Vector2 Vector2::normal(bool right)
{
	float arg = argumento();
	if (right) arg += 90;
	else arg -= 90;
	Vector2 aux = direccion(arg);
	aux = aux * modulo();
	return aux;
}

Vector2 Vector2::direccion(float a)
{
	Vector2 aux;
	aux.x = cos(a);
	aux.y = sin(a);
	return aux;
}

//float Vector2::check_angle(float a)
//{
//
//}
#pragma once
#include <SDL.h>
#include <cmath>

class Vector2
{
public:

	Vector2(float px = 0, float py = 0);
	Vector2(SDL_Point p);
	~Vector2();

	//Coordenadas
	float x, y;

	//Pasar a int
	SDL_Point convert_int();

	//Operators
	Vector2 operator - (Vector2 v);
	Vector2 operator + (Vector2 v);
	Vector2 operator * (float k);
	Vector2 operator = (Vector2 v);
	Vector2 operator += (Vector2 v);
	Vector2 operator -= (Vector2 v);
	Vector2 operator *= (float k);
	Vector2 operator = (SDL_Point p);
	

	float length();
	float angle(); //degrees
	float radians();
	float distance(Vector2 dest);

	Vector2 normalize(float n = 1.0);
	Vector2 normal(bool right = true);

	static Vector2 toVector(float a);

};


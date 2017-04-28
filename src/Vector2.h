#pragma once
#include <SDL.h>
#include <cmath>

class Vector2
{
public:

	//Constructor
	Vector2(float px = 0, float py = 0);
	Vector2(SDL_Point p);

	//Destructor
	~Vector2();

	//Coordenadas
	float x, y;

	//Pasar a int
	SDL_Point convert_int();

	//Operators
	Vector2 operator - (Vector2 v);
	Vector2 operator + (Vector2 v);
	Vector2 operator = (Vector2 v);
	Vector2 operator += (Vector2 v);
	Vector2 operator -= (Vector2 v);
	Vector2 operator = (SDL_Point p);

	Vector2 operator * (float k);

	float distancia(Vector2 dest);
	Vector2 norm(float n = 1.0);
	Vector2 normal(bool right = true);
	float modulo();
	float argumento();

	static Vector2 direccion(float a);
//	static float check_angle(float a);
};


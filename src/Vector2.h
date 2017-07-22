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
	Vector2 operator -  (Vector2 v);
	Vector2 operator +  (Vector2 v);
	Vector2 operator *  (float k);
	Vector2 operator =  (Vector2 v);
	Vector2 operator += (Vector2 v);
	Vector2 operator -= (Vector2 v);
	Vector2 operator *= (float k);
	Vector2 operator =  (SDL_Point p);
	Vector2 operator - ();

	bool operator == (Vector2 v);
	bool operator != (Vector2 v);

	float projection(Vector2 v); //scalar projection
	float operator *  (Vector2 v); //scalar product
	float crossProduct(Vector2 v);

	float length();
	float angle(); //degrees
	float radians();
	float distance(Vector2 dest);
	float angle(Vector2 v);

	Vector2 normalize(float n = 1.0);
	Vector2 normal(bool right = true);
	Vector2 rotatedTo(float angle);
	Vector2 aligned(Vector2 v);
	Vector2 rotateBy(float angle);
	void makeZero();

	static Vector2 toVector(float angle, float length = 1.0F);
	static Vector2 zero();

};


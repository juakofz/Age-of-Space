#include "Vector2.h"
#include <math.h>


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

Vector2::~Vector2()
{

}


SDL_Point Vector2::convert_int()
{
	SDL_Point ret;
	ret.x = static_cast<int>(x);
	ret.y = static_cast<int>(y);
	return ret;
}

Vector2 Vector2::operator + (Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (Vector2 v)
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (float k)
{
	return Vector2(k*x, k*y);
}

Vector2 Vector2::operator / (float k)
{
	return Vector2(k/x, k/y);
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

Vector2 Vector2::operator *= (float k)
{
	x *= k;
	y *= k;
	return *this;
}

Vector2 Vector2::operator /= (float k)
{
	x /= k;
	y /= k;
	return *this;
}

Vector2 Vector2::operator = (SDL_Point p)
{
	x = static_cast<float>(p.x);
	y = static_cast<float>(p.y);
	return(Vector2(x, y));
}

bool Vector2::operator == (Vector2 v)
{
	if (x == v.y && y == v.y) return true;
	else return false;
}

bool Vector2::operator != (Vector2 v)
{
	if (x != v.y || y != v.y) return true;
	else return false;
}

float Vector2::projection(Vector2 v)
{
	float angle_aux = angle() - v.angle();
	return length() * cos(angle_aux * M_PI / 180);
}

float Vector2::operator * (Vector2 v)
{
	return projection(v) * v.length();
}

float Vector2::crossProduct(Vector2 v)
{
	float k = x * v.y - y * v.x;
	return k;
}

float Vector2::length()
{
	return sqrt(x * x + y * y);
}

float Vector2::angle()
{
	float aux;
	aux = 180 * atan2(y, x) / M_PI;
	if (aux<0) return (aux + 360);
	else return aux;
}

float Vector2::radians()
{	
	return atan2(y, x);
}

float Vector2::distance(Vector2 dest)
{
	Vector2 aux = dest - *this;
	return aux.length();
}

float Vector2::angle(Vector2 v)
{
	float dot = (*this * v);
	float det = crossProduct(v);
	float angle = atan2(det, dot) * 180 / M_PI;
	return angle;
}

Vector2 Vector2::normalize(float n)
{
	if (length() < 0.0001f)
	{
		Vector2 zero(0, 0);
		return zero;
	}

	Vector2 aux;
	aux.x = n * x / length();
	aux.y = n * y / length();
	return aux;
}

Vector2 Vector2::normal(bool right)
{
	float arg = angle();
	if (right) arg += 90;
	else arg -= 90;
	Vector2 aux = toVector(arg);
	aux = aux * length();
	return aux;
}

Vector2 Vector2::rotatedTo(float angle)
{
	Vector2 aux = toVector(angle).normalize(length());
	return aux;
}

void Vector2::rotateTo(float angle)
{
	Vector2 aux = toVector(angle).normalize(length());
	*this = aux;
}

Vector2 Vector2::aligned(Vector2 v)
{
	Vector2 aux = rotatedTo(v.angle());
	return aux;
}

Vector2 Vector2::rotateBy(float angle)
{
	if (this->angle() + angle >= 360)
		angle -= 360;
	if (this->angle() + angle < 0)
		angle += 360;
	
	Vector2 aux = toVector(this->angle() + angle).normalize(length());
	return aux;
}

void Vector2::makeZero()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::toVector(float angle, float scale)
{
	Vector2 aux;
	aux.x = cos(angle * M_PI / 180);
	aux.y = sin(angle * M_PI / 180);
	aux.normalize(scale);
	return aux;
}

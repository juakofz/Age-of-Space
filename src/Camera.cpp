#include "Camera.h"

Camera::Camera()
{
	cen.x = cen.y = frame.w = frame.h = frame.x = frame.y = 0;
	zoom = 1;
}


Camera::~Camera()
{
}

//Actualizar
void Camera::update(ViewPort v)
{
	frame.w = v.GetParam().w;
	frame.h = v.GetParam().h;

	setCen(cen.x, cen.y);
	//cout << "Update" << endl;
}


//Movimiento y zoom
void Camera::move(float mx, float my)
{
	cen.x += mx;
	cen.y += my;

	frame.x += mx;
	frame.y += my;
}

void Camera::changeZoom(float z)
{
	zoom += z;
}

//Margen de renderizado
bool Camera::isVisible(Vector2 pos, int margin)
{
	margin = -margin;
	if ((pos.x - margin >= frame.x) && (pos.x + margin <= frame.x + frame.w))
	{
		if ((pos.y - margin >= frame.y) && (pos.y + margin <= frame.y + frame.h))
			return true;
	}
	return false;
}

//Posición
Vector2 Camera::getPos()
{
	Vector2 temp;
	temp.x = frame.x;
	temp.y = frame.y;

	return temp;
}

void Camera::setPos(float x, float y)
{
	frame.x = x;
	frame.y = y;

	cen.x = frame.x + frame.w / 2;
	cen.y = frame.y + frame.h / 2;
}

//Centro
Vector2 Camera::getCen()
{
	return cen;
}

void Camera::setCen(float x, float y)
{
	cen.x = x;
	cen.y = y;

	frame.x = cen.x - frame.w / 2;
	frame.y = cen.y - frame.h / 2;
}

//Tamaño
void Camera::setSize(int w, int h)
{
	frame.w = w;
	frame.h = h;

	frame.x = cen.x - frame.w / 2;
	frame.y = cen.y - frame.h / 2;
}

Vector2 Camera::getSize()
{
	Vector2 temp;
	temp.x = frame.w;
	temp.y = frame.h;
	return temp;
}
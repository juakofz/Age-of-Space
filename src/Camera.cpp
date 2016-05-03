#include "Camera.h"



Camera::Camera()
{	
}


Camera::~Camera()
{
}

//Rect
SDL_Rect Camera::getRect()
{
	return rect;
}

void Camera::setRect(SDL_Rect r)
{
	rect = r;
}


//Centro
Vector2 Camera::getCen()
{
	return center;
}

void Camera::setCen(float x, float y)
{
	center.x = x;
	center.y = y;
	update();
}

void Camera::moveX(float x)
{
	center.x += x;
	cout << "mierda grande y seca" << center.x << endl;
	cout << endl;
	update();
}

void Camera::moveY(float y)
{
	center.y += y;
	update();
}

void Camera::update()
{
	rect.x = center.x - rect.w / 2;
	rect.y = center.y - rect.h / 2;
	cout << "update!  --  " << center.x << "  --  " << center.y << endl;
	cout << endl;
}

//Zoom
void Camera::setZoom(float z)
{
	zoom = z;
}

float Camera::getZoom()
{
	return zoom;
}

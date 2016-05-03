#pragma once
#include <SDL.h>
#include "Vector2.h"
#include <iostream>

using namespace std;

class Camera
{
public:
	Camera();
	~Camera();

	//Rect
	SDL_Rect getRect();
	void setRect(SDL_Rect r);

	//Centro
	Vector2 getCen();
	void setCen(float x, float y);
	void moveX(float x);
	void moveY(float y);
	void update();

	//Zoom
	void setZoom(float z);
	float getZoom();

private:
	SDL_Rect rect;
	Vector2 center;

	float zoom;
};


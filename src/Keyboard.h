#pragma once
#include <SDL.h>
#include "Camera.h"


class Keyboard
{
public:
	
	Keyboard();
	
	~Keyboard();

	void update(SDL_Event *e, Camera c);

	//void moveCamera();
};


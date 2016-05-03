#pragma once
#include <SDL.h>

class Keyboard
{
public:
	
	Keyboard();
	
	~Keyboard();

	void update(SDL_Event *e);

	void moveCamera();
};


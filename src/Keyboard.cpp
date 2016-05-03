#include "Keyboard.h"
#include <iostream>

using namespace std;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

void Keyboard::update(SDL_Event *e, Camera c)
{
	//Scroll
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_UP:
			c.moveY(-2.0);
			cout << "UP!  --  " << c.getCen().y << endl;
			break;
		case SDLK_DOWN:
			c.moveY(2.0);
			cout << "DOWN!  --  " << c.getCen().y << endl;
			break;
		case SDLK_LEFT:
			c.moveX(-2.0);
			cout << "LEFT!  --  " << c.getCen().x << endl;
			break;
		case SDLK_RIGHT:
			c.moveX(2.0);
			cout << "RIGHT!  --  " << c.getCen().y << endl;
			break;

		//case SDLK_BACKSPACE:
			//break;
		}
	}
}

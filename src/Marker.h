#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Vector2.h"

class Ship;

class Marker
{
	friend class Ship;
public:
	Marker(/*SDL_Point c, int h, int w, SDL_Color cl*/);
	~Marker();

	void draw(SDL_Renderer *renderer);
	
	void setCen(SDL_Point c);

	void setSize(int h, int w);

	void setColor(SDL_Color cl);

	void update();

private:
	SDL_Point center, top_right, top_left, bottom_right, bottom_left;
	
	int height, width;
	
	SDL_Color color;	
};


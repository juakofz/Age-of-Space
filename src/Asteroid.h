#pragma once


#include "GameObject.h"


extern SDL_Renderer* gRenderer;
class Texture;

class Asteroid: public GameObject

{
public:
	//Constructor
	Asteroid();

	//Destructor
	~Asteroid();

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);

};

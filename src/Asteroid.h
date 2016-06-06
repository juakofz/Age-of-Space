#pragma once
#include "GameObject.h"

//pepe

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
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);

};

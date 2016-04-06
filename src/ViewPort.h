#pragma once
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Global.h"

//extern SDL_Window* gWindow;
//extern SDL_Renderer* gRenderer;

class ViewPort
{
	SDL_Rect param;
	Texture tex;
	Vector2 origen, tamaño, tamañofin;

public:
	//constructor
	ViewPort(void);

	//destructor
	~ViewPort(void);

	//parametros
	void Init(int x, int y, int w, int h,std::string path);
	void ActParam();

	void SetRel(float x, float y, float w, float h);
	void SetParam( int w, int h, int x=NULL, int y=NULL);
	SDL_Rect GetParam();
	
	//renderizar
	void render();

};


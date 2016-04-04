#pragma once
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

class ViewPort
{
	SDL_Rect param;
	Texture tex;
public:
	//constructor
	ViewPort(void);

	//destructor
	~ViewPort(void);

	//parametros
	void Init(int x, int y, int w, int h,std::string path);

	void SetParam(int x, int y, int w, int h);
	SDL_Rect GetParam();

	//renderizar
	void render();

};


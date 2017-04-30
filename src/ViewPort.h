#pragma once
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Global.h"


class ViewPort
{
private:

	SDL_Rect m_param; //Viewport data
	Texture m_tex; //Background texture

	//proporciones y tamaño final -- ??
	Vector2 origen, tamaño, tamañofin;

public:

	ViewPort();
	ViewPort(SDL_Rect rect);
	~ViewPort();

	//inicializar
	void Init(int x, int y, int w, int h,std::string path);

	//parametros
	void ActParam();
	void SetParam( int w, int h, int x=NULL, int y=NULL);
	SDL_Rect getParam();

	//relacion de tamaño respecto a la pantalla
	void SetRel(float x, float y, float w, float h);

	//altura y corrdonada y
	int getHeight();
	int getWidth();
	int getY();

	//renderizar
	void render();
	void Set();

	//relativiza la posicion del raton a sus coordenadas
	SDL_Point relatxy();
	SDL_Point relatxy(int x, int y);

};


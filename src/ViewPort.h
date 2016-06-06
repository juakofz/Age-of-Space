#pragma once
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Global.h"


class ViewPort
{
	//datos del viewport
	SDL_Rect param;
	Texture tex;

	//proporciones y tamaño final
	Vector2 origen, tamaño, tamañofin;

public:
	//constructor
	ViewPort(void);

	//destructor
	~ViewPort(void);

	//inicializar
	void Init(int x, int y, int w, int h,std::string path);

	//parametros
	void ActParam();
	void SetParam( int w, int h, int x=NULL, int y=NULL);
	SDL_Rect GetParam();

	//relacion de tamaño respecto a la pantalla
	void SetRel(float x, float y, float w, float h);

	//altura y corrdonada y
	int getHeight();
	int getY();

	//renderizar
	void render();
	void Set();

	//relativiza la posicion del raton a sus coordenadas
	SDL_Point relatxy();
	SDL_Point relatxy(int x, int y);

};


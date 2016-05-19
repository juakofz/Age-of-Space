#pragma once

#include "Global.h"

class Caracteristicas
{
	Texture nombre, imagen;
	Vector2 nombredim, imagendim;

public:
	Caracteristicas(void);
	~Caracteristicas(void);
	void render();
	void event(SDL_Event* e, SDL_Point xyrel);
	void setDim(Vector2 nombre, Vector2 imagen);
};


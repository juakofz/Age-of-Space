#pragma once

#include "ViewPort.h"
#include <SDL.h>
#include "LWindow.h"
#include "Asteroid.h"


class EnteSupremo
{
	ViewPort barra, juego, menus, total;
	Asteroid ast;

public:

	EnteSupremo(void);
	~EnteSupremo(void);

	//funciones con viewports
	void setViewPort(SDL_Event* e);
	void InitViewPorts();
	void ActViewPorts();
	void RenderViewPorts();

	//eventos
	void event(SDL_Event* e);
	void RenderTotal();

	//asteroides
	void initjuego();
	void renderJuego();
};


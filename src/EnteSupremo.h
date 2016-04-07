#pragma once

#include "ViewPort.h"
#include <SDL.h>
#include "LWindow.h"
#include "Asteroid.h"
#include "Barra.h"

class EnteSupremo
{
	ViewPort barra, juego, menus, total;
	Asteroid ast;
	Barra menubarra;
	string nombrejugador;

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

	void setNombre(std::string nombre);
};


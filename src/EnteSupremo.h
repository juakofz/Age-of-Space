#pragma once

#include "ViewPort.h"
#include <SDL.h>
#include "LWindow.h"
#include "Asteroid.h"
#include "Barra.h"
#include "Mouse.h"
#include "Timer.h"
#include "Ship.h"
#include "Mouse.h"

class EnteSupremo
{
	//viewports del juego
	ViewPort barra, juego, menus, total;

	//elementos del juego
	Asteroid ast;
	Ship ship;

	//añadidos que hay que recolocar
	Barra menubarra;
	string nombrejugador;

	//texturas
	Texture tex[5];

	//Mouse
	Mouse mouse;
	SDL_Rect mouse_selection;

public:

	EnteSupremo(void);
	~EnteSupremo(void);

	//carga las texturas
	void cargarTexturas();


	//funciones con viewports
	void InitViewPorts(); //inicializa los viewports
	void ActViewPorts(); //actualiza los viewports con cambio en la ventana
	void RenderViewPorts(); //renderiza los viewports

	//eventos
	void event(SDL_Event* e); //reparte los eventos al viewport en el que nos encontremos
	void RenderTotal(); //renderiza la pantalla de inicio


	//juego
	void initjuego(); //inicializa los elementos del juego
	void renderJuego(); //renderiza los elementos del juego
	void eventjuego(SDL_Event* e); //eventos en el viewport del juego 

	//nombre del jugador
	void setNombre(std::string nombre);
};


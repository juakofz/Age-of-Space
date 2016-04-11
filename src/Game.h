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
#include "Player.h"

class Game
{
	//viewports del juego
	ViewPort barra, juego, menus, total;

	//elementos del juego
	Asteroid ast;
	Ship ship[60];

	//a�adidos que hay que recolocar
	Barra menubarra;
	string nombrejugador;
	Menu menu;
	Player jugador;

	//texturas
	Texture tex[5];
	Texture texOpciones[3];

	//Mouse
	Mouse mouse;
	SDL_Rect mouse_selection;

public:

	Game(void);
	~Game(void);

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


	//menu
	void initMenu(); //inicializa los elementos del juego
	void renderMenu(); //renderiza los elementos del juego
	void eventMenu(SDL_Event* e); //eventos en el viewport del juego 

	//nombre del jugador
	void setNombre(std::string nombre);
};


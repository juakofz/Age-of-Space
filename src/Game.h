<<<<<<< HEAD
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
#include "Caracteristicas.h"
#include "Global.h"
#include "Map.h"

class Game
{
	//viewports del juego
	ViewPort barra, juego, menus, total;
	int numviewport;

	//Mapa
	Map map;

	//Mouse
	Mouse mouse;

	//Camara
	Camera cam;

	//elementos del juego
	Asteroid ast;
	Ship ship[60];

	//añadidos que hay que recolocar
	Barra menubarra;
	//string nombrejugador;
	Menu menu;
	Player jugador;
	Caracteristicas caract;

	//texturas
	Texture tex[10];
	Texture texOpciones[5];

	SDL_Point posicion;

	characts* chooseElement(int type);

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
	
	//Eventos fuera de cola
	void main_event();

	//juego
	void initjuego(); //inicializa los elementos del juego
	void renderJuego(); //renderiza los elementos del juego
	void eventjuego(SDL_Event* e); //eventos en el viewport del juego 


	//menu
	void initMenu(); //inicializa los elementos del juego
	void renderMenu(); //renderiza los elementos del juego
	void eventMenu(SDL_Event* e); //eventos en el viewport del juego 


	//caracteristicas
	void initCaract(); //inicializa los elementos del juego
	void renderCaract(); //renderiza los elementos del juego
	void eventCaract(SDL_Event* e); //eventos en el viewport del juego 

	//barra
	void initBarra(); //inicializa los elementos del juego
	void renderBarra(); //renderiza los elementos del juego
	void eventBarra(SDL_Event* e); //eventos en el viewport del juego 

	//nombre del jugador
	void setNombre(std::string nombre);
};

=======
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
#include "Caracteristicas.h"
#include "Global.h"

class Game
{
	//viewports del juego
	ViewPort barra, juego, menus, total;
	int numviewport;

	//elementos del juego
	Asteroid ast;
	Ship ship[60];

	//añadidos que hay que recolocar
	Barra menubarra;
	//string nombrejugador;
	Menu menu;
	Player jugador;
	Caracteristicas caract;

	//texturas
	Texture tex[10];
	Texture texOpciones[5];

	//Mouse
	Mouse mouse;
	SDL_Rect mouse_selection;

	characts* chooseElement(int type);

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


	//caracteristicas
	void initCaract(); //inicializa los elementos del juego
	void renderCaract(); //renderiza los elementos del juego
	void eventCaract(SDL_Event* e); //eventos en el viewport del juego 

	//barra
	void initBarra(); //inicializa los elementos del juego
	void renderBarra(); //renderiza los elementos del juego
	void eventBarra(SDL_Event* e); //eventos en el viewport del juego 

	//nombre del jugador
	void setNombre(std::string nombre);
};

>>>>>>> origin/master

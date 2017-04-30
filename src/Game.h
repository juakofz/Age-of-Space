#pragma once

#include <SDL.h>
#include "Window.h"
#include "Barra.h"
#include "Mouse.h"
#include "Timer.h"
//#include "Ship.h"
#include "Player.h"
#include "Global.h"
#include "Map.h"
//#include "ListaAsteroides.h"
//#include "ListaNaves.h"
//#include "ListaProyectiles.h"
//#include "ListaObjetos.h"
//#include "ListaExplosiones.h"
//#include "Proyectil.h"
#include "ScreenArea.h"
//#include "Menu.h"
//#include "MovingObject.h"
//#include "Interacciones.h"
//#include "Edificio.h"
//#include "Controller.h"


class Game
{
	//Sreen areas
	ScreenArea *areas[AREA_NUMBER];
	ScreenArea game_area, orders_area, info_area, map_area, window_area;
	Barra top_bar;

	Mouse mouse; //Mouse	
	Map map; //Map
	Camera cam; //Camara

	////Controlador
	//Controller control;

	////elementos del juego
	//Edificio edificio;
	//ListaAsteroides asteroides;
	//ListaNaves naves;
	//ListaObjetos objetos_prueba;
	//ListaProyectiles proyectiles;
	//Asteroid ast;

	bool act_barra, act_vida;

	Player player1;

	//texturas
	Texture tex[15];
	Texture texOpciones[5];

	SDL_Point posicion;

	static int ataques;
	static bool atacar;

public:

	Game(void);
	~Game(void);

	//carga las texturas
	void cargarTexturas();

	void InitViewPorts(); //inits viewports
	void UpdateViewPorts(); //updates viewports when the screen is resized
	void RenderViewPorts();

	//eventos
	int event(SDL_Event* e); //reparte los eventos al viewport en el que nos encontremos
	void RenderTotal(); //renderiza la pantalla de inicio
	
	//Eventos fuera de cola
	void main_event();

	//juego
	void initjuego(); //inicializa los elementos del juego
	void reinitjuego(); //devuelve los objetos a su posicion original
	void nuevafase(int i);
	void renderJuego(); //renderiza los elementos del juego
	int gameEvents(SDL_Event* e); //eventos en el viewport del juego 


	//menu
	void initMenu(); //inicializa los elementos del juego
	void renderMenu(); //renderiza los elementos del juego
	void eventMenu(SDL_Event* e); //eventos en el viewport del juego 

	//barra
	void initBarra(int fase); //inicializa los elementos del juego
	void renderBarra(); //renderiza los elementos del juego
	void eventBarra(SDL_Event* e); //eventos en el viewport del juego 
	
	//Minimapa
	void initMinimapa(); //inicializa los elementos del juego
	void renderMinimapa(); //renderiza los elementos del juego
	void eventMinimapa(SDL_Event* e); //eventos en el viewport del juego


	//nombre del jugador
	void setNombre(std::string nombre);

	//Naves enemigas
	void ataqueEnemigo();
};
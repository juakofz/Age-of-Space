#pragma once


#include <SDL.h>
#include "LWindow.h"
#include "Barra.h"
#include "Mouse.h"
#include "Timer.h"
#include "Ship.h"
#include "Mouse.h"
#include "Player.h"
#include "Caracteristicas.h"
#include "Global.h"
#include "Map.h"
#include "ListaAsteroides.h"
#include "ListaNaves.h"
#include "ListaProyectiles.h"
#include "ListaObjetos.h"
#include "ListaExplosiones.h"
#include "Proyectil.h"
#include "ZonaPantalla.h"
#include "Menu.h"
#include "ObjetoMovil.h"
#include "Interacciones.h"
#include "Edificio.h"

enum ZONAS
{
	BARRA=0,
	JUEGO=1,
	MENU=2,
	MINIMAPA=3,
	TOTAL=4,
	NUM_VIEWPORTS=5
};

class Game
{
	//viewports del juego
//	ViewPort  juego, total;
	int numviewport;

	ZonaPantalla *zonas[NUM_VIEWPORTS];
	ZonaPantalla juego, total, minimapa;
	//Mapa
	Map map;

	//Mouse
	Mouse mouse;

	//Camara
	Camera cam;

	//elementos del juego
	Edificio edificio;
	ListaAsteroides asteroides;
	ListaNaves naves;
	ListaObjetos objetos_prueba;
	ListaProyectiles proyectiles;
	Asteroid ast;



	//Partes de la pantalla
	Menu menu;
	Barra barra;

	Player jugador;
	Caracteristicas caract;

	//texturas
	Texture tex[15];
	Texture texOpciones[5];

	SDL_Point posicion;

	characts* chooseElement(int type);

	static int ataques;
	static bool atacar;

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

	//Naves enemigas
	static Uint32 LlamadaAtaqueEnemigo(Uint32 interval, void* param);
	void ataqueEnemigo();
};
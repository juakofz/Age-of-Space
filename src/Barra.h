#pragma once
#include <string>
#include "Texture.h"
#include "ZonaPantalla.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra: public ZonaPantalla
{
	// name;
	Texture nombrejugador, opciones, recursos, energianum, oronum, fasenum, vida;
	SDL_Color color;
			

public:

	Barra(void);
	~Barra(void);

	void render();

	//void actRecursos();
	void renderRecursos();
	void setRecursos(std::stringstream recursos[]);

	//nombre del jugador
	void SetName(std::string nombre);
	void renderName();

	//numero de fase
	void SetFase(int fase);
	void renderFase();

	//vida del edificio
	void setVida(int vid);
	void renderVida();

	int event(SDL_Event* e, SDL_Point xyrel);
};


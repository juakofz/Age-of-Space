#pragma once
#include <string>
#include "Texture.h"
#include "ZonaPantalla.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra: public ZonaPantalla
{
	// name;
	Texture nombrejugador, opciones, recursos, energianum, oronum, fasenum;


public:

	Barra(void);
	~Barra(void);

	void render();

	//void actRecursos();
	void renderRecursos();
	void setRecursos(std::stringstream recursos[]);

	//nombre del jugador
	void SetName(std::string fase);
	void renderName();

	//numero de fase
	void SetFase(int fase);
	void renderFase();

	//void renderOpciones();

	int event(SDL_Event* e, SDL_Point xyrel);
};


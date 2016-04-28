#pragma once
#include <string>
#include "Texture.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra
{
	// name;
	Texture nombrejugador, opciones, recursos, energianum, oronum;


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

	//void renderOpciones();

	void event(SDL_Event* e, SDL_Point xyrel);
};


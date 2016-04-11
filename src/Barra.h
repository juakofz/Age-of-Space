#pragma once
#include <string>
#include "Texture.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra
{
	// name;
	Texture nombrejugador, opciones, recursos;
	Texture oroVal, energiaVal;

public:

	Barra(void);
	~Barra(void);

	void render(std::stringstream recursos[]);

	//void actRecursos();
	void renderRecursos(std::stringstream recursos[]);
	void setRecursos(std::stringstream recursos[]);

	//nombre del jugador
	void SetName(std::string nombre);
	void renderName();

	//void renderOpciones();
};


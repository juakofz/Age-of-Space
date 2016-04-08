#pragma once
#include <string>
#include "Texture.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra
{
	// name;
	Texture nombrejugador, opciones, recursos;

public:

	Barra(void);
	~Barra(void);

	void render();

	//void actRecursos();
	void renderRecursos();

	//nombre del jugador
	void SetName(std::string nombre);
	void renderName();

	//void renderOpciones();
};


#pragma once
#include <string>
#include "Texture.h"


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

	void SetName(std::string nombre);
	void renderName();

	//void renderOpciones();
};


#pragma once
#include <string>
#include "Texture.h"
<<<<<<< HEAD

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra
=======
#include "ZonaPantalla.h"

//esta clase todavia esta en pañales, no hay que hacerle mucho caso

class Barra: public ZonaPantalla
>>>>>>> refs/remotes/origin/pr/8
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

<<<<<<< HEAD
	void event(SDL_Event* e, SDL_Point xyrel);
=======
	int event(SDL_Event* e, SDL_Point xyrel);
>>>>>>> refs/remotes/origin/pr/8
};


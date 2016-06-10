#pragma once

#include <vector>
#include "Edificio.h"

class ListaEdificios
{

	std::vector<Edificio*> lista;
public:

	ListaEdificios(void);
	~ListaEdificios(void);
	bool agregar(Edificio *edif);
	void render(Camera cam);
	void eliminarEdificio(int ind);
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	int getSel();
};


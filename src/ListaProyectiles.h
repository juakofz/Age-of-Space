#pragma once

#include <vector>
#include "Proyectil.h"
#include "Camera.h"
#include "ListaNaves.h"

class ListaProyectiles
{

	std::vector<Proyectil*> lista;
public:

	ListaProyectiles(void);
	~ListaProyectiles(void);
	bool agregar(Proyectil *proy);
	void render(Camera cam);
	void eliminarProyectil(int ind);
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	int getSel();

	void impacto(ListaNaves l);
};


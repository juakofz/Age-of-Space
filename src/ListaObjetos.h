#pragma once

#include <vector>
#include "GameObject.h"
#include "Camera.h"

class ListaObjetos
{

	std::vector<GameObject*> lista;

public:

	ListaObjetos(void);
	~ListaObjetos(void);
	bool agregar(GameObject* elemento);
	void render(Camera cam);
	void eliminarElemento(int ind);
	int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	int getSel();
};
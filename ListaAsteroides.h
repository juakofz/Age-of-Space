#pragma once

#include <vector>
#include "Asteroid.h"
#include "Camera.h"

class ListaAsteroides
{
	std::vector<Asteroid*> lista;

public:

	ListaAsteroides(void);
	~ListaAsteroides(void);
	bool agregar(Asteroid *ast);
	void render(Camera cam);
	void eliminarAsteroide(int ind);
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	int getSel();
};

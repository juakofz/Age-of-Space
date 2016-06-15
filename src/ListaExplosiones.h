#pragma once

#include <vector>
#include "Explosion.h"

class Explosion;

class ListaExplosiones
{
	friend class Interacciones;
	std::vector<Explosion*> lista;
public:
	ListaExplosiones(void);
	~ListaExplosiones(void);

	bool agregar(Explosion *proy);
	void render(Camera cam);
	void eliminar(int ind);

};
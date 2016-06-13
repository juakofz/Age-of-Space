#pragma once

#include "Ship.h"
#include "Proyectil.h"
#include "ListaNaves.h"
#include "ListaProyectiles.h"

class Interacciones
{
public:
	Interacciones(void);
	~Interacciones(void);
	static bool impacto(Ship nave, Proyectil disparo);
	static bool impactoListas(ListaNaves &n, ListaProyectiles &p);

};
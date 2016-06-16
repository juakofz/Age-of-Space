#pragma once

#include "Ship.h"
#include "Proyectil.h"
#include "ListaNaves.h"
#include "ListaProyectiles.h"
#include "Edificio.h"

class Interacciones
{
public:
	Interacciones(void);
	~Interacciones(void);
	static bool impacto(Ship nave, Proyectil disparo);
	static int impactoListas(ListaNaves &n, ListaProyectiles &p);
	static bool impacto(Edificio &edif, ListaProyectiles &disparo);
	static bool impacto(Edificio edif, Proyectil disparo);

};

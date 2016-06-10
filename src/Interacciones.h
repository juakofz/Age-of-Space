#pragma once

#include "Ship.h"
#include "Proyectil.h"

class Interacciones
{
public:
	Interacciones(void);
	~Interacciones(void);
	static bool impacto(Ship nave, Proyectil disparo);

};


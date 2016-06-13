#pragma once

#include "objetomovil.h"


class Proyectil :
	public ObjetoMovil
{
public:
	Proyectil(bool amig=true);
	~Proyectil(void);
	bool move();
};


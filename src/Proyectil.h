#pragma once

#include "objetomovil.h"


class Proyectil :
	public ObjetoMovil
{
public:
	Proyectil(int p = 1);
	~Proyectil(void);
	bool move();
};

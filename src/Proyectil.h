#pragma once

#include "MovingObject.h"


class Proyectil :
	public MovingObject
{
public:
	Proyectil(int p = 1);
	~Proyectil(void);
	bool move();
};

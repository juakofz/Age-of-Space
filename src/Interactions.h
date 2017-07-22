#pragma once
#include "Ship.h"
#include "Projectile.h"
#include "Station.h"



class Interactions
{
public:
	Interactions();
	~Interactions();

	static float calculateDamage(Ship * ship, Projectile * proj);
	static float calculateDamage(GameObject * ship, GameObject * proj);
	static float calculateDamage(Station * station, Projectile * proj);
};


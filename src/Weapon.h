#pragma once
#include "Station.h"



class Weapon : public Station
{
public:
	Weapon();
	~Weapon();

	bool update();
	bool update(Ship * owner);
};


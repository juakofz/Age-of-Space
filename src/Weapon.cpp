#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}


bool Weapon::update()
{
	return false;
}

bool Weapon::update(Ship * owner)
{
	//Non predictive shooting
	return false;
}
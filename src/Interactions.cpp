#include "Interactions.h"



Interactions::Interactions()
{
}


Interactions::~Interactions()
{
}

float Interactions::calculateDamage(Ship * ship, Projectile * proj)
{
	float aux_dmg = proj->getDmg();
	return aux_dmg;
}

float Interactions::calculateDamage(Station * station, Projectile * proj)
{
	float aux_dmg = proj->getDmg();
	return aux_dmg;
}
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

float Interactions::calculateDamage(GameObject * ship, GameObject * proj)
{
	if (ship->getType() == TYPE_SHIP && proj->getType() == TYPE_PROJECTILE)
	{
		float aux_dmg = dynamic_cast<Projectile *>(proj)->getDmg();
		return aux_dmg;
	}

}

float Interactions::calculateDamage(Station * station, Projectile * proj)
{
	float aux_dmg = proj->getDmg();
	return aux_dmg;
}
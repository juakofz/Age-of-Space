#include "Station.h"



Station::Station()
{
}


Station::~Station()
{
}

int Station::getType()
{
	return m_type;
}

bool Station::damage(float d)
{
	if (m_max_health == 0) //Non damageable
		return false;

	if (d < 0) d = 0;
	m_health -= d;
	if (m_health <= 0)
		return true;
	else
		return false;
}
#include "ExplosionVector.h"



ExplosionVector::ExplosionVector()
{
}


ExplosionVector::~ExplosionVector()
{
	if (!v_explosions.empty())
		v_explosions.clear();
}

bool ExplosionVector::in(int i)
{
	if (!v_explosions.empty() && i <= v_explosions.size())
		return true;
	else
		return false;
}

void ExplosionVector::add(Explosion * explosion)
{
	v_explosions.push_back(explosion);
}

void ExplosionVector::erase(int i)
{
	if (in(i))
		v_explosions.erase(v_explosions.begin() + i); //Remove and destroy object
}

void ExplosionVector::update()
{
	//do things
}

int ExplosionVector::count()
{
	if (v_explosions.empty())
		return 0;
	else
		return v_explosions.size();
}

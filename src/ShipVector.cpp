#include "ShipVector.h"



ShipVector::ShipVector()
{
}


ShipVector::~ShipVector()
{
	//Clear vector if there is any element remaining
	if (!v_ship.empty())
		v_ship.clear();
}

bool ShipVector::in(int i)
{
	if (!v_ship.empty() && i <= v_ship.size())
		return true;
	else
		return false;
}

void ShipVector::add(Ship * ship)
{
	v_ship.push_back(ship);
}

void ShipVector::erase(int i)
{
	if (in(i))
		v_ship.erase(v_ship.begin() + i); //Remove and destroy object
}

void ShipVector::render(Camera cam)
{
	if (v_ship.empty()) return;
	else
	{
		for (int i = 0; i < v_ship.size(); i++)
		{
			v_ship[i]->render(cam);
		}
	}
}

void ShipVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!v_ship.empty()) //if list is not empty
	{
		for (int i = 0; i < v_ship.size(); i++)
		{
			v_ship[i]->event(e, sel, xy_rel);
		}
	}
}

void ShipVector::move()
{
	if (!v_ship.empty()) //if list is not empty
	{
		for (int i = 0; i < v_ship.size(); i++)
		{
			v_ship[i]->move();
		}
	}
}

bool ShipVector::damage(int i, float damage)
{
	if (in(i))
	{
		if (v_ship[i]->damage(damage))
			return true;
	}
	return false;
}
int ShipVector::count()
{
	if (v_ship.empty())
		return 0;
	else
		return v_ship.size();
}

Ship * ShipVector::get(int i)
{
	if (in(i))
	{
		Ship * aux_ship = v_ship[i];
		return aux_ship;
	}
	else
		return NULL;
}

Vector2 ShipVector::getCen(int i)
{
	Vector2 aux;
	if (!in(i))
		return aux; //Zero
	else
	{
		aux = v_ship[i]->getCen();
		return aux;
	}
}

float ShipVector::getSize(int i)
{
	if (!in(i))
		return 0;
	else
		return v_ship[i]->getSize();
}

bool ShipVector::getSel(int i)
{
	if (in(i))
	{
		return v_ship[i]->getSel();
	}
	else return false;
}
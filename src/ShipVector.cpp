#include "ShipVector.h"



ShipVector::ShipVector()
{
}


ShipVector::~ShipVector()
{
	//Clear vector if there is any element remaining
	if (!v_elements.empty())
		v_elements.clear();
}

void ShipVector::render(Camera cam)
{
	if (v_elements.empty()) return;
	else
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->render(cam);
		}
	}
}

void ShipVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->event(e, sel, xy_rel);
		}
	}
}

void ShipVector::update()
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->update();
		}
	}
}

void ShipVector::move()
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->move();
		}
	}
}



void ShipVector::repel(int i, int j)
{
	if (in(i) && in(j))
	{
		Vector2 aux_repulsion = v_elements[i]->getCen() - v_elements[j]->getCen();
		if (aux_repulsion.length() < 0.001 )
			aux_repulsion = (0, 1);
		float repel_force = 0.03f;

		v_elements[i]->addVel(aux_repulsion.normalize(repel_force)); //Repel ship i
		v_elements[j]->addVel(- aux_repulsion.normalize(repel_force)); //Repel ship j in opposite direction
	}
}


bool ShipVector::damage(int i, float damage)
{
	if (in(i))
	{
		if (v_elements[i]->damage(damage))
			return true;
	}
	return false;
}


Vector2 ShipVector::getCen(int ind)
{
	Vector2 aux;
	if (!in(ind))
		return aux; //Zero
	else
	{
		aux = v_elements[ind]->getCen();
		return aux;
	}
}

float ShipVector::getSize(int ind)
{
	if (!in(ind))
		return 0;
	else
		return v_elements[ind]->getSize();
}

bool ShipVector::getSel(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getSel();
	}
	else return false;
}

int ShipVector::getPlayer(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getPlayer();
	}
	else return false;
}
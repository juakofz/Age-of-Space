#include "ObjectVector.h"



Vector2 ObjectVector::getCen(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getCen();
	}
	else return Vector2::zero();
}


float ObjectVector::getSize(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getSize();
	}
	else return 0.0f;
}


bool ObjectVector::getSel(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getSel();
	}
	else return false;
}


int ObjectVector::getPlayer(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getPlayer();
	}
	else return 0;
}

int ObjectVector::getType(int ind)
{
	if (in(ind))
	{
		return v_elements[ind]->getType();
	}
	else return 0;
}


void ObjectVector::render(Camera cam)
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


void ObjectVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->event(e, sel, xy_rel);
		}
	}
}


void ObjectVector::update()
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->update();
		}
	}
}


void ObjectVector::move()
{
	if (!v_elements.empty()) //if list is not empty
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			
			bool f_dead = v_elements[i]->move();

			if (v_elements[i]->getType() == TYPE_PROJECTILE && f_dead)
			{
				erase(i);
			}
		}
	}
}


void ObjectVector::repel(int ind, Vector2 dir)
{
	if (v_elements[ind]->getType() == TYPE_SHIP)
	{
		//cout << "Repel" << endl;
	}
}


bool ObjectVector::damage(int ind, float damage)
{
	return false;
}
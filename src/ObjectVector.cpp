#include "ObjectVector.h"


ObjectVector::ObjectVector()
{
}


ObjectVector::~ObjectVector()
{
	if(!v_objects.empty())
		v_objects.clear();
}

bool ObjectVector::in(int i)
{
	if (!v_objects.empty() && i <= v_objects.size())
		return true;
	else
		return false;
}

void ObjectVector::add(GameObject * object)
{
	v_objects.push_back(object);
}

void ObjectVector::erase(int i)
{
	if (in(i))
	{
		//Remove and destroy object
		v_objects.erase(v_objects.begin() + i);
	}
}

void ObjectVector::clear()
{
	v_objects.clear();
}


void ObjectVector::render(Camera cam)
{
	if (v_objects.empty()) return;
	else
	{
		for (int i = 0; i < v_objects.size(); i++)
		{
			v_objects[i]->render(cam);
		}
	}
}

void ObjectVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!v_objects.empty()) //if list is not empty
	{
		for (int i = 0; i < v_objects.size(); i++)
		{
			v_objects[i]->event(e, sel, xy_rel);
		}
	}
}

int ObjectVector::count()
{
	if (v_objects.empty())
		return 0;
	else
		return v_objects.size();
}

bool ObjectVector::getSel(int i)
{
	if (in(i))
	{
		return v_objects[i]->getSel();
	}
	else return false;
}
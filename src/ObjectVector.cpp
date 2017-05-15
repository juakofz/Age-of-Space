#include "ObjectVector.h"


ObjectVector::ObjectVector()
{
}


ObjectVector::~ObjectVector()
{
}

bool ObjectVector::in(int i)
{
	if (!objectVector.empty() && i <= objectVector.size())
		return true;
	else
		return false;
}

void ObjectVector::add(GameObject * object)
{
	objectVector.push_back(object);
}

void ObjectVector::erase(int i)
{
	if (in(i))
	{
		//Remove and destroy object
		objectVector.erase(objectVector.begin() + i);
	}
}

void ObjectVector::render(Camera cam)
{
	if (objectVector.empty()) return;
	else
	{
		for (int i = 0; i < objectVector.size(); i++)
		{
			objectVector[i]->render(cam);
		}
	}
}

void ObjectVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!objectVector.empty()) //if list is not empty
	{
		for (int i = 0; i < objectVector.size(); i++)
		{
			objectVector[i]->event(e, sel, xy_rel);
		}
	}
}

int ObjectVector::count()
{
	if (objectVector.empty())
		return 0;
	else
		return objectVector.size();
}

bool ObjectVector::getSel(int i)
{
	if (in(i))
	{
		return objectVector[i]->getSel();
	}
	else return false;
}
#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

bool ObjectManager::in(int i)
{
	if (!objectVector.empty() && i <= objectVector.size())
		return true;
	else
		return false;
}

void ObjectManager::add(GameObject * object)
{
	objectVector.push_back(object);
}

void ObjectManager::erase(int i)
{
	if (in(i))
	{
		//Remove and destroy object
		objectVector.erase(objectVector.begin() + i);
	}
}

void ObjectManager::render(Camera cam)
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

void ObjectManager::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!objectVector.empty()) //if list is not empty
	{
		for (int i = 0; i < objectVector.size(); i++)
		{
			objectVector[i]->event(e, sel, xy_rel);
		}
	}
}

int ObjectManager::count()
{
	if (objectVector.empty())
		return 0;
	else
		return objectVector.size();
}

bool ObjectManager::getSel(int i)
{
	if (in(i))
	{
		return objectVector[i]->getSel();
	}
	else return false;
}
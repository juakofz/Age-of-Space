#include "MovingObjectVector.h"



MovingObjectVector::MovingObjectVector()
{
}


MovingObjectVector::~MovingObjectVector()
{
	if (!v_movingObjects.empty())
		v_movingObjects.clear();
}

bool MovingObjectVector::in(int i)
{
	if (!v_movingObjects.empty() && i <= v_movingObjects.size())
		return true;
	else
		return false;
}

void MovingObjectVector::add(MovingObject * movingObject)
{
	v_movingObjects.push_back(movingObject);
}

void MovingObjectVector::erase(int i)
{
	if (in(i))
	{
		//Remove and destroy object
		v_movingObjects.erase(v_movingObjects.begin() + i);
	}
}

void MovingObjectVector::clear()
{
	v_movingObjects.clear();
}


void MovingObjectVector::render(Camera cam)
{
	if (v_movingObjects.empty()) return;
	else
	{
		for (int i = 0; i < v_movingObjects.size(); i++)
		{
			v_movingObjects[i]->render(cam);
		}
	}
}

void MovingObjectVector::event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	if (!v_movingObjects.empty()) //if list is not empty
	{
		for (int i = 0; i < v_movingObjects.size(); i++)
		{
			v_movingObjects[i]->event(e, sel, xy_rel);
		}
	}
}

void MovingObjectVector::move()
{
	if (v_movingObjects.empty()) return;
	else
	{
		for (int i = 0; i < v_movingObjects.size(); i++)
		{
			if (v_movingObjects[i]->move())
			{
				erase(i);
			}
		}
	}
}

int MovingObjectVector::count()
{
	if (v_movingObjects.empty())
		return 0;
	else
		return v_movingObjects.size();
}

bool MovingObjectVector::getSel(int i)
{
	if (in(i))
	{
		return v_movingObjects[i]->getSel();
	}
	else return false;
}
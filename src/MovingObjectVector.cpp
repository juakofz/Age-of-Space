#include "MovingObjectVector.h"



MovingObjectVector::MovingObjectVector()
{
}


MovingObjectVector::~MovingObjectVector()
{
}

void MovingObjectVector::move()
{
	if (objectVector.empty()) return;
	else
	{
		for (int i = 0; i < objectVector.size(); i++)
		{
			if (movingObjectVector[i]->move())
			{
				erase(i);
			}
		}
	}

}
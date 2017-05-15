#pragma once
#include "ObjectVector.h"
#include "MovingObject.h"

class MovingObjectVector : public ObjectVector
{
public:
	MovingObjectVector();
	~MovingObjectVector();

	virtual void move();
protected:
	vector<MovingObject * > movingObjectVector;
};


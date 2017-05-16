#pragma once
#include <vector>
#include "MovingObject.h"

class MovingObjectVector
{
public:
	MovingObjectVector();
	~MovingObjectVector();
	
	bool in(int i);

	void add(MovingObject * movingObject);
	void erase(int i);
	void clear();

	void render(Camera cam);
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);
	void move();

	int count();
	bool getSel(int ind);

	
private:
	vector<MovingObject * > v_movingObjects;
};
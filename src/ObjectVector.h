#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

class ObjectVector
{
public:
	ObjectVector();
	~ObjectVector();

	bool in(int i);

	void add(GameObject * object);
	void erase(int i);

	virtual void render(Camera cam);
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);

	int count();
	bool getSel(int ind);

protected:
	vector<GameObject *> objectVector;
};


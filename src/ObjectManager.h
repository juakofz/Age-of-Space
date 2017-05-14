#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	bool in(int i);

	void add(GameObject * object);
	void erase(int i);

	void render(Camera cam);
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);

	int count();
	bool getSel(int ind);

private:
	vector<GameObject *> objectVector;
};


#pragma once
#include "T_Vector.h"
#include "GameObject.h"

using namespace std;

class ObjectVector: public T_Vector<GameObject>
{
public:
	
	//Get
	Vector2 getCen(int ind);
	float getSize(int ind);
	bool getSel(int ind);
	int getPlayer(int ind);
	int getType(int ind);

	void render(Camera cam);
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);

	void update();
	void move();

	void repel(int ind, Vector2 dir);
	bool damage(int ind, float damage);

};


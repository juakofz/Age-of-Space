#pragma once
#include "Ship.h"
#include <vector>

class ShipVector
{
public:
	ShipVector();
	~ShipVector();

	bool in(int i);

	void add(Ship * ship);
	void erase(int i);

	void render(Camera cam);
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);
	void update();
	void move();
<<<<<<< HEAD
	void repel(int i, int j);
=======
>>>>>>> origin/rework
	bool damage(int i, float damage);

	int count();
	Ship * get(int i);

	Vector2 getCen(int i);
	float getSize(int i);
	bool getSel(int ind);

protected:
	vector<Ship *> v_ship;
};


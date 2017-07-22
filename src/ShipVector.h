#pragma once
#include "Ship.h"
#include "T_Vector.h"

class ShipVector: public T_Vector<Ship>
{
public:
	ShipVector();
	~ShipVector();

	void render(Camera cam);//
	void event(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);//
	void update();//
	void move();//
	void repel(int i, int j);
	bool damage(int i, float damage);

	Vector2 getCen(int i);//
	float getSize(int i);//
	bool getSel(int ind);//
	int getPlayer(int ind);//

};


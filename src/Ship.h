#pragma once

#include "Texture.h"
#include "Camera.h"
#include "MovingObject.h"
#include "Timer.h"

class Texture;

class Ship:public MovingObject
{
public:
	
	Ship();
	Ship(Texture *texture, int siz, Texture *marktex, Vector2 cen, int player = 0);
	~Ship();

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	bool disparada(Proyectil p);
	Vector2 getPointyEnd();

	//Range
	float getRange();
	bool inRange(Vector2 p);
	bool inRange(GameObject * s);
	bool inRange();

	//Sight
	float getSight();
	bool inSight(Vector2 p);
	bool inSight(GameObject *s);
	bool inSight();

	bool attack();
	Vector2 shoot();

	int getState();
	void setState(int s);

	Timer * getTimer();

	bool turn();
	void turn(Vector2 t);
	bool move();

	void setTarget(GameObject * t);
	bool checkTarget();
	void updateTarget();
	GameObject * getTarget();
	bool onTarget(Vector2 t, float err = 5.0);
	bool onTarget(float err = 5.0);
	float targetDist();

private:

	GameObject * target;

	int state;
	float range;
	float sight;
	float firerate; //Frec
	Timer order;
	Timer t_shoot;

	//Marker
	SDL_Color marker_color;
	float sel_radius;
	Texture sel_circle;
};
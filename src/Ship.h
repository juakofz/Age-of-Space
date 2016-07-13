#pragma once

#include "Texture.h"
#include "Camera.h"
#include "ObjetoMovil.h"
#include "Proyectil.h"
#include "Timer.h"

class Texture;

class Ship:public ObjetoMovil
{
public:
	
	Ship();
	Ship(Texture *texture, int siz, Texture *marktex, Vector2 cen, int p = 0, bool sel = false);
	~Ship();

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	bool disparada(Proyectil p);
	Vector2 getPointyEnd();

	//Range
	float getRange();
	bool inRange(Vector2 p);
	bool inRange(Ship * s);

	//Sight
	float getSight();
	bool inSight(Vector2 p);
	bool inSight(Ship *s);

	bool attack();
	Vector2 shoot();

	int getState();
	void setState(int s);

	Timer * getTimer();

	bool turn();
	void turn(Vector2 t);

	void setTarget(Ship * t);
	bool checkTarget();
	void updateTarget();
	Ship * getTarget();
	bool onTarget(Vector2 t, float err = 5.0);
	bool onTarget(float err = 5.0);
	float targetDist();

private:

	Ship * target;

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
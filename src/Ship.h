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

	//Event management
	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
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

	//Movement
	bool move();
	bool f_follow_mouse; //For funsies

	void setTarget(GameObject * t);
	bool checkTarget();
	void updateTarget();
	GameObject * getTarget();
	bool onTarget(Vector2 t, float err = 5.0);
	bool onTarget(float err = 5.0);
	float targetDist();

private:

	void setup();

	GameObject * m_target;

	int m_state;
	float m_sight;
	float m_range;
	Timer t_order;

	//Marker
	SDL_Color m_marker_color;
	float m_sel_radius;
	Texture m_sel_circle;
};
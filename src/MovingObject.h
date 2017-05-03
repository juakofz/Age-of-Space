#pragma once
#include "GameObject.h"
#include "timer.h"

class MovingObject :
	public GameObject
{
public:

	MovingObject(int type, int player);
	~MovingObject(void);

	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	void render(Camera cam);

	//Movimiento
	virtual bool move() = 0;
	void stop();
	void moveStraight(int x, int y);

	//Velocidad
	Vector2 GetVel();
	void SetVel(float x, float y);

	//Direction
	Vector2 GetDir();
	void SetDir(float x, float y);

	//Destination
	void setDest(float x, float y);
	Vector2 getDest();
	bool onPoint(Vector2 p);
	bool onDest();

protected:

	//Movement
	Vector2 m_vel;
	Vector2 m_accel;
	float m_friction; //0 to 1;
	float m_max_accel;
	Vector2 m_dir;
	Vector2 m_dest;
	bool f_following;
};


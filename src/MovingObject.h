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
	virtual void render(Camera cam);
	virtual void renderDebug(Camera cam);

	//Movement
	virtual bool move();
	void stop();
	void moveStraight(int x, int y);

	//Velocity
	Vector2 getVel();
	void setVel(float x, float y);
	void setVel(Vector2 vel);

	//Speed -- used for linear movement
	float getSpeed();
	void setSpeed(float s);

	//Direction
	Vector2 getDir();
	void setDir(float x, float y);
	void setDir(Vector2 dir);

	//Angle
	float getAngle();
	void setAngle(float a);

	//Destination
	void setDest(float x, float y);
	void setDest(Vector2 dest);
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
	float m_steer_limit;
	float m_speed;
};


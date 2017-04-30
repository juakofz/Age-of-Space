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
	virtual bool move();
	virtual bool turn(int x, int y);
	void stop();
	bool moveTo(int x, int y);

	Vector2& getDest();

	//Velocidad
	Vector2 GetVel();
	void SetVel(float x, float y);
	void SetMaxVel(float v);

	//Dirección
	Vector2 GetDir();
	void SetDir(float x, float y);

	void setDest(float x, float y);
	bool onPoint(Vector2 p);
	bool onDest();

protected:

	//Movement
	Vector2 vel;
	Vector2 acc;
	float friction; //0 to 1;
	float max_vel;
	float max_acc;
	Vector2 dir;
	Vector2 dest;
	float turn_rad;

	//Seguimiento
	float* dest_movil_x, *dest_movil_y;
	bool following;
};


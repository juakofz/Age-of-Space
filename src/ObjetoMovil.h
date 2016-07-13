#pragma once
#include "gameobject.h"
#include "timer.h"

class ObjetoMovil :
	public GameObject
{
public:


	ObjetoMovil(int t, bool selec = true);
	~ObjetoMovil(void);

	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	void render(Camera cam);

	//Movimiento
	virtual bool move();
	bool turn(int x, int y);
	void stop();
	bool moveTo(int x, int y);
	void follow(Vector2 &destino);
	
	Vector2& getDest();

	//Velocidad
	Vector2 GetVel();
	void SetVel(float x, float y);
	void SetMaxVel(float v);

	//Dirección
	Vector2 GetDir();
	void SetDir(float x, float y);

protected:

	float max_vel;
	Vector2 vel;
	Vector2 accel;
	Vector2 dir;
	Vector2 dest;
	float turn_rad;

	//Seguimiento
	float* dest_movil_x, *dest_movil_y;
	bool following;
};


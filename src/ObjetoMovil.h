#pragma once
#include "gameobject.h"

class ObjetoMovil :
	public GameObject
{
public:



	ObjetoMovil(void);
	~ObjetoMovil(void);

	void event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);

	//Movimiento
	void move();
	void stop();
	bool moveTo(int x, int y);

	//Velocidad
	Vector2 GetVel();
	void SetVel(float x, float y);

	//Dirección
	Vector2 GetDir();
	void SetDir(float x, float y);

protected:

	float max_vel;
	Vector2 vel;
	Vector2 dir;
	Vector2 dest;
};


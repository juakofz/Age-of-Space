#pragma once
#include "Texture.h"
#include "Vector2.h"

class Ship
{
public:
	//Constructor
	Ship();

	//Destructor
	~Ship();

	//Manejo de eventos
	void event(SDL_Event* e);

	//Selección
	void select();
	void deselect();

	//Movimiento
	void move();
	bool moveTo(int x, int y);

	//Renderizado
	void render(SDL_Renderer* renderer);

	//Posición
	Vector2 GetPos();
	void SetPos(float x, float y);

	//Velocidad
	Vector2 GetVel();
	void SetVel(float x, float y);

	//Dirección
	Vector2 GetDir();
	void SetDir(float x, float y);

	Texture tex;

private:

	Vector2 pos;
	Vector2 vel;
	Vector2 dir;

	bool sel;
	float sel_radius;
	Texture sel_circle;
};
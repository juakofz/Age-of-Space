#pragma once
#include "Texture.h"
#include "Camera.h"
#include "ObjetoMovil.h"
#include "Proyectil.h"
class Texture;

class Ship:public ObjetoMovil
{
public:
	//Constructor
	Ship();

	//Destructor
	~Ship();

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	int shoot();
	bool disparada(Proyectil p);
	//Selección
	//void select();
	//void deselect();

	//Movimiento
	//void move();
	//void stop();
	//bool moveTo(int x, int y);

	//Renderizado
	//void render(SDL_Renderer* renderer, Camera cam);
	//void setMarker(Texture *m);

	//Posición
	//Vector2 GetPos();
	//void SetPos(float x, float y);

	//Velocidad
	//Vector2 GetVel();
	//void SetVel(float x, float y);

	//Dirección
	//Vector2 GetDir();
	//void SetDir(float x, float y);

	//Centro
	//Vector2 GetCen();
	//void SetCen(float x, float y);

	//Textura
	//void SetTex(Texture *t);
	//friend class Texture;

	//Tamaño
	//void setSize(int s);

private:

	//Texture *tex;
	//Texture *marker;

	SDL_Color marker_color;

	//int size;
	//int width;
	//int height;

	//float max_vel;
	//float angle;

	//Vector2 pos;
	//Vector2 vel;
	//Vector2 dir;
	//Vector2 cen;
	//Vector2 dest;

	//bool sel;
	//int sel_angle;
	float sel_radius;
	Texture sel_circle;
};
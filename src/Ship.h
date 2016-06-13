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
	Ship(Texture *texture,int siz, Texture *marktex, Vector2 cen, bool amig=true);
	//Destructor
	~Ship();

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m);
	int shoot();
	bool disparada(Proyectil p);
	Vector2 getPointyEnd();

	int attack(Ship &n);

private:

	SDL_Color marker_color;

	float sel_radius;
	Texture sel_circle;
};
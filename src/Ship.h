#pragma once

#include "Texture.h"
#include "Camera.h"
#include "ObjetoMovil.h"
#include "Proyectil.h"


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
	float getRange();

	int attack(Ship &n);

private:

	float range;

	//Marker
	SDL_Color marker_color;
	float sel_radius;
	Texture sel_circle;
};
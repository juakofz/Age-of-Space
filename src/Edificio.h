#pragma once
#include "gameobject.h"

class Edificio:public GameObject
{
public:
	Edificio(void);
	~Edificio(void);

	//Manejo de eventos
	int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool golpeada();

	void setVida(int v);
	int getVida() {return vida;}

private:
	int vida;
};
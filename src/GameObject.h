#pragma once

#include "Texture.h"
#include "Camera.h"
#include "Global.h"

class GameObject
{
public:

	//constructor y destructor
	GameObject(void);
	GameObject(bool selec=true);
	virtual ~GameObject(void);

	//Manejo de eventos
	virtual void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)=0;

	//Selecci�n
	void select();
	void deselect();
	bool getSel();


	//Renderizado
	virtual void render(Camera cam);
	void setMarker(Texture *m);

	//Posici�n
	Vector2 GetPos();
	virtual void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	virtual void SetCen(float x, float y);

	void SetTex(Texture *t);

	//Tama�o
	void setSize(int s);

	int getType();

protected:

	Texture *marker, *tex;
	//posicion y centro
	Vector2 pos;
	Vector2 cen;

	int size;
	int width;
	int height;
	float angle;

	//flag de seleccion
	bool sel;
	bool seleccionable;
	int sel_angle;
};


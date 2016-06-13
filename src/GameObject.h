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
	virtual int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)=0;

	//Selección
	void select();
	void deselect();
	bool getSel();
	bool clickOn(SDL_Point pos);

	//Renderizado
	virtual void render(Camera cam);
	void setMarker(Texture *m);

	//Posición
	Vector2 GetPos();
	virtual void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	Vector2& getCen(); 
	void giveCen(Vector2 &dest);
	void getCen(float &x, float &y);
	virtual void SetCen(float x, float y);

	void SetTex(Texture *t);

	//Tamaño
	void setSize(int s);
	int getSize();
	Vector2 getDim();

	int getType();

	//propia
	bool getAmiga();
	void setAmiga(bool amig);

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

	int sel_angle;

	//propia
	bool amiga;

private:
	bool seleccionable;

};


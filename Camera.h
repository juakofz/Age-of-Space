#pragma once
#include "Vector2.h"
#include "ViewPort.h"

class ViewPort;

class Camera
{
public:
	Camera();
	~Camera();

	//Actualizar
	void update(ViewPort v);

	//Movimiento y zoom
	void move(float mx, float my);
	void changeZoom(float z);

	//Margen de renderizado
	bool isVisible(Vector2 pos, int margin = 0);

	//Posición
	Vector2 getPos();
	void setPos(float x, float y);

	//Centro
	Vector2 getCen();
	void setCen(float x, float y);

	//Tamaño
	void setSize(int w, int h);
	Vector2 getSize();

private:
		
	SDL_Rect frame;
	Vector2 cen;
	float zoom;
};

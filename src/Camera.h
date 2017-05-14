#pragma once
#include "Vector2.h"
#include "ViewPort.h"

class ViewPort;

class Camera
{
public:
	Camera();
	~Camera();

	void scroll();
	void update(ViewPort v);

	//Movimiento y zoom
	void move(float mx, float my);
	void changeZoom(float z);

	//Margen de renderizado
	bool isVisible(Vector2 pos, int margin = 0);

	//Posición
	SDL_Point getPos();
	void setPos(float x, float y);

	//Centro
	Vector2 getCen();
	void setCen(float x, float y);

	//Tamaño
	void setSize(int w, int h);
	Vector2 getSize();

private:
		
	SDL_Rect m_frame;
	Vector2 m_cen;
	float m_zoom;
	bool f_up, f_down, f_left, f_right;
};

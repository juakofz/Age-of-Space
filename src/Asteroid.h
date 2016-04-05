#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Button.h"
#include "Menu.h"

extern SDL_Renderer* gRenderer;

class Asteroid

{
public:
	//Constructor
	Asteroid();

	//Destructor
	~Asteroid();

	//Manejo de eventos
	void event(SDL_Event* e);

	//Selección
	void select();
	void deselect();

	//menu
	void SetMenu(int w, int h);
	void openMenu();

	//Renderizado
	void render();

	//Posición
	Vector2 GetPos();
	void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	void SetCen(float x, float y);

	Texture tex;

private:
	Menu menu;
	Button boton;
	Vector2 pos;
	Vector2 cen;

	bool sel;
	float sel_radius;
	Texture sel_circle;
};


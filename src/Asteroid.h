#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Button.h"

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

	//Selecci�n
	void select();
	void deselect();

	//menu
	void openMenu(SDL_Renderer* renderer);

	//Renderizado
	void render();

	//Posici�n
	Vector2 GetPos();
	void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	void SetCen(float x, float y);

	Texture tex;

private:
	Button boton;
	Vector2 pos;
	Vector2 cen;

	bool sel;
	float sel_radius;
	Texture sel_circle;
};


<<<<<<< HEAD
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
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);

	//Selección
	void select();
	void deselect();
	bool getSel();

	//Renderizado
	void render();
	void setMarker(Texture *m);

	//Posición
	Vector2 GetPos();
	void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	void SetCen(float x, float y);

	void SetTex(Texture *t);

	//Tamaño
	void setSize(int s);

	int getType();

private:

	Texture *tex;
	Texture *marker;
	SDL_Color marker_color;

	//posicion y centro
	Vector2 pos;
	Vector2 cen;

	int size;

	//flag de seleccion
	bool sel;
	int sel_angle;
};

=======
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
	void event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);

	//Selección
	void select();
	void deselect();
	bool getSel();

	//Renderizado
	void render();
	void setMarker(Texture *m);

	//Posición
	Vector2 GetPos();
	void SetPos(float x, float y);

	//Centro
	Vector2 GetCen();
	void SetCen(float x, float y);

	void SetTex(Texture *t);

	//Tamaño
	void setSize(int s);

	int getType();

private:

	Texture *tex;
	Texture *marker;
	SDL_Color marker_color;

	//posicion y centro
	Vector2 pos;
	Vector2 cen;

	int size;

	//flag de seleccion
	bool sel;
	int sel_angle;
};

>>>>>>> refs/remotes/origin/development

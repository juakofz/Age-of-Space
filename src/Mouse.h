#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Texture.h"
#include "Camera.h"

class Camera;

class Mouse
{
public:
	Mouse();
	~Mouse();

	//Cursor
	void setCursor(Texture * c);
	
	//Manejo de eventos
	bool update(SDL_Event *e, SDL_Point xyrel);
	
	//Movimiendo de c�mara
	void scroll(Camera cam);

	//Render de efectos
	void render(SDL_Renderer *renderer);
	//Selecci�n m�ltiple
	//void selection();

	//Devuelve selecci�n
	SDL_Rect getSel();

private:
	Texture *cursor;

	SDL_Point pos;
	SDL_Point press;
	SDL_Point release;

	SDL_Rect rect;
	bool active;
};


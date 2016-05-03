#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
<<<<<<< HEAD
#include "Texture.h"
=======
>>>>>>> refs/remotes/origin/development

class Mouse
{
public:
	Mouse();
	~Mouse();

<<<<<<< HEAD
	//Cursor
	void setCursor(Texture * c);
	
	//Manejo de eventos
	void update(SDL_Event *e, SDL_Point xyrel);
=======
	//Manejo de eventos
	void update(SDL_Event *e);
>>>>>>> refs/remotes/origin/development

	//Render de efectos
	void render(SDL_Renderer *renderer);
	//Selección múltiple
	//void selection();

	//Devuelve selección
	SDL_Rect getSel();

private:
<<<<<<< HEAD
	Texture *cursor;

=======
>>>>>>> refs/remotes/origin/development
	SDL_Point pos;
	SDL_Point press;
	SDL_Point release;

	SDL_Rect rect;
	bool active;
};


#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
<<<<<<< HEAD
<<<<<<< HEAD
#include "Texture.h"
=======
>>>>>>> refs/remotes/origin/development
=======
#include "Texture.h"
#include "Camera.h"

class Camera;
>>>>>>> refs/remotes/origin/development

class Mouse
{
public:
	Mouse();
	~Mouse();

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/development
	//Cursor
	void setCursor(Texture * c);
	
	//Manejo de eventos
<<<<<<< HEAD
	void update(SDL_Event *e, SDL_Point xyrel);
=======
	//Manejo de eventos
	void update(SDL_Event *e);
>>>>>>> refs/remotes/origin/development
=======
	bool update(SDL_Event *e, SDL_Point xyrel);
	
	//Movimiendo de cámara
	void scroll(Camera cam);
>>>>>>> refs/remotes/origin/development

	//Render de efectos
	void render(SDL_Renderer *renderer);
	//Selección múltiple
	//void selection();

	//Devuelve selección
	SDL_Rect getSel();

private:
<<<<<<< HEAD
<<<<<<< HEAD
	Texture *cursor;

=======
>>>>>>> refs/remotes/origin/development
=======
	Texture *cursor;

>>>>>>> refs/remotes/origin/development
	SDL_Point pos;
	SDL_Point press;
	SDL_Point release;

	SDL_Rect rect;
	bool active;
};


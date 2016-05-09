#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Texture.h"
#include "Camera.h"
#include "Map.h"

class Camera;
class Map;

class Mouse
{
public:
	Mouse();
	~Mouse();

	//Cursor
	void setCursor(Texture * c);
	
	//Event management
	bool update(SDL_Event *e, SDL_Point xyrel);
	
	//Camera movement (map scrolling)
	void scroll(Camera &cam, Map map);

	//Mouse render
	void render(SDL_Renderer *renderer, SDL_Point posicion);

	//Get relative selection
	SDL_Rect getSel();

private:
	//Cursor texture
	Texture *cursor;

	//Relative to viewpory
		//Mouse position
		SDL_Point r_pos;
		//Press position
		SDL_Point r_press;	
		//Selection rect
		SDL_Rect r_rect;

	//Selection rect - ?
	SDL_Rect rect_abs;

	//Selection marker
	bool active;
};


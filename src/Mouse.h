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
	void update(SDL_Event *e, bool sel = true);
	
	//Camera movement (map scrolling)
	void scroll(Camera &cam, Map map);

	//Mouse render
	void render(SDL_Renderer *renderer = gRenderer);


	//Get relative selection
	SDL_Rect getSel();

	//Absolute position
	void setPos(int px, int py);
	SDL_Point getPos();

	//Relative position (to viewport)
	void setR_pos(int px, int py);
	SDL_Point getR_pos();
	
	//Map position
	void setMpos(int px, int py);
	SDL_Point getMpos();
	SDL_Rect getMrect();

	//Selection
	bool isActive();

private:
	//Cursor texture
	Texture *cursor;

	//Absolute
		//Mouse positio
		SDL_Point pos;
		//Press position
		SDL_Point press;
		//Selection rect
		SDL_Rect rect;

	//Relative to viewpory
		//Mouse position
		SDL_Point r_pos;
		//Press position
		SDL_Point r_press;	
		//Selection rect
		SDL_Rect r_rect;

	//Relative to map
		//Mouse position
		SDL_Point m_pos;
		//Press position
		SDL_Point m_press;
		//Selection rect
		SDL_Rect m_rect;

	//Selection marker
	bool active;
};


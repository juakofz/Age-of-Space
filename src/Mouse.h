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
	void update(SDL_Event *e, int area, bool sel);
	
	//Camera movement (map scrolling)
	void scroll(Camera &cam, Map map);

	//Mouse render
	void render(SDL_Renderer *renderer = g_Renderer);

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

	//Relative to viewport
		//Mouse position
		SDL_Point m_viewport_pos;
		//Press position
		SDL_Point m_viewport_press;	
		//Selection rect
		SDL_Rect m_viewport_rect;

	//Relative to map
		//Mouse position
		SDL_Point m_map_pos;
		//Press position
		SDL_Point m_map_press;
		//Selection rect
		SDL_Rect m__map_rect;

	bool f_active; //selection flag
	int m_area;
};


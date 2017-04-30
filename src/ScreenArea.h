#pragma once

#include "ViewPort.h"

class ScreenArea
{

protected:

	ViewPort viewport;

public:

	ScreenArea(void);

	~ScreenArea(void);

	virtual void render();
	virtual int event(SDL_Event* e, SDL_Point xyrel);
	virtual void Open();

	//Funciones para los viewports
	void initViewPort(SDL_Rect rect, std::string path = "");
	void initViewPort(float x1, float y1, float x2, float y2, std::string path = ""); //Relative to screen sizes
	void SetRel(float x, float y, float w, float h);
	void update();
	void renderViewport();
	void Set();

	int up();
	int down();
	int left();
	int right();

	int getHeight();
	int getWidth();


	ViewPort getViewport();

	SDL_Point relatxy();
	SDL_Point relatxy(int x, int y);
};


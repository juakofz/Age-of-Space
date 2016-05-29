#pragma once

#include "ViewPort.h"

class ZonaPantalla
{

protected:

	ViewPort viewport;

public:

	ZonaPantalla(void);

	~ZonaPantalla(void);

	//Funciones polimórficas
	virtual void render();

	virtual int event(SDL_Event* e, SDL_Point xyrel);

	virtual void Open();

	//Funciones para los viewports
	void initViewport(int x, int y, int w, int h,std::string path);
	void SetRel(float x, float y, float w, float h);
	void ActParam();
	void renderViewport();
	void Set();
	int getY();
	int getHeight();

	ViewPort getViewport();

	SDL_Point relatxy();
	SDL_Point relatxy(int x, int y);
};


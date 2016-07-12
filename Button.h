#pragma once
#include "Texture.h"

//esta clase ahora mismo no se utiliza

extern SDL_Renderer* gRenderer;


class Button
{

private:

	//Top left position
	Vector2 pos;
	bool sel;
	Texture *tex;
	Vector2 size;

public:

	Button(void);

	~Button(void);

	//Sets top left position
	void setPos( int x, int y );

	//Handles mouse event
	bool event( SDL_Event* e, SDL_Point xyrel );
	
	//Shows button sprite
	void render(Vector2 botondim);

	//nos indica si hemos clicado encima, hayqque cambiar las coordenadas
	bool clickOn(SDL_Event* e, SDL_Point xyrel);

	void setTexture(Texture *t);
};


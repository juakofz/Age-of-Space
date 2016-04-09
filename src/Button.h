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
	Texture tex;

public:

	Button(void);

	~Button(void);

	//Sets top left position
	void setPos( int x, int y );

	//Handles mouse event
	void event( SDL_Event* e );
	
	//Shows button sprite
	void render();

	//nos indica si hemos clicado encima, hayqque cambiar las coordenadas
	bool clickOn(SDL_Event* e);


};


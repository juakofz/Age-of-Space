#pragma once
#include "Texture.h"

extern SDL_Renderer* gRenderer;

class Asteroid;
class Menu;

class Button
{

	friend class Asteroid;
	friend class Menu;

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

	bool clickOn(SDL_Event* e);


};


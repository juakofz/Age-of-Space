#pragma once

#include "Button.h"
#include "Texture.h"

const int NUMERO_BOTONES=3;

class Menu
{
	Button botones[NUMERO_BOTONES];
	Vector2 botondim;
	//Texture texturas[NUMERO_BOTONES];

public:

	Menu(void);
	~Menu(void);
	void SetBotones();
	void render();
	void SetBotonQuad(int w, int h);
	void event(SDL_Event* e);
};


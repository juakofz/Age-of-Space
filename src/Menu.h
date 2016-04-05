#pragma once

#include "Button.h"
#include "Texture.h"

const int NUMERO_BOTONES=3;

class Menu
{
	Button botones[NUMERO_BOTONES];
	SDL_Rect botonQuad;
	Texture texturas[NUMERO_BOTONES];

public:

	Menu(void);
	~Menu(void);
	void SetBotones();
	void render();
	void SetBotonQuad(int x, int y, int w, int h);
};


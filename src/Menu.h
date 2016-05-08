<<<<<<< HEAD
#pragma once

#include "Button.h"
#include "Texture.h"

const int NUMERO_BOTONES=3;
const int NUMERO_BOT_GENERALES=2;
//esto ahora mismo no se utiliza

class Menu
{
	Button botones[NUMERO_BOTONES];
	Button botonesgenerales[NUMERO_BOT_GENERALES];
	Vector2 botondim;
	//Texture *texturas[NUMERO_BOTONES];

public:

	Menu(void);
	~Menu(void);
	void setBotones(Texture tex[]);
	void render();
	void setBotonQuad(int w, int h);
	void event(SDL_Event* e, SDL_Point xyrel);
	//void setTexturas(Texture tex[]);
};

=======
#pragma once

#include "Button.h"
#include "Texture.h"

const int NUMERO_BOTONES=3;
const int NUMERO_BOT_GENERALES=2;
//esto ahora mismo no se utiliza

class Menu
{
	Button botones[NUMERO_BOTONES];
	Button botonesgenerales[NUMERO_BOT_GENERALES];
	Vector2 botondim;
	//Texture *texturas[NUMERO_BOTONES];

public:

	Menu(void);
	~Menu(void);
	void setBotones(Texture tex[]);
	void render();
	void setBotonQuad(int w, int h);
	void event(SDL_Event* e, SDL_Point xyrel);
	//void setTexturas(Texture tex[]);
};

>>>>>>> refs/remotes/origin/development

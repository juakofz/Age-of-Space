#pragma once

#include "Button.h"
<<<<<<< HEAD
#include "Texture.h"
=======
#include "ZonaPantalla.h"
>>>>>>> refs/remotes/origin/pr/8

const int NUMERO_BOTONES=3;
const int NUMERO_BOT_GENERALES=2;
//esto ahora mismo no se utiliza

<<<<<<< HEAD
class Menu
{
=======
class Menu: public ZonaPantalla
{
protected:

>>>>>>> refs/remotes/origin/pr/8
	Button botones[NUMERO_BOTONES];
	Button botonesgenerales[NUMERO_BOT_GENERALES];
	Vector2 botondim;
	//Texture *texturas[NUMERO_BOTONES];

public:

	Menu(void);
	~Menu(void);
	void setBotones(Texture tex[]);
	void render();
<<<<<<< HEAD
	void setBotonQuad(int w, int h);
	void event(SDL_Event* e, SDL_Point xyrel);
=======
	void Open();
	void setBotonQuad(int w, int h);
	int event(SDL_Event* e, SDL_Point xyrel);
>>>>>>> refs/remotes/origin/pr/8
	//void setTexturas(Texture tex[]);
};


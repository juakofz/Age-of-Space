#pragma once

#include "Game.h"

class Coordinator
{
public:
	Coordinator(void);
	~Coordinator(void);

	void initGame();
	void mainEvent();
	void event(SDL_Event *e);
	void actViewports();
	void render();

protected:
	Game game;

	enum Estado {INICIO, INTRO_FASE, JUEGO, PAUSE, GAMEOVER};
	Estado estado;

	int fase;

	//texto de la pantalla de inicio
	std::string inputText;
	int tamaño;
	SDL_Color textColor;
	bool renderText;
	Timer tiempo_fase, tiempo_ataques;
};


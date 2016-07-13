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

	//estados
	enum Estado {INICIO, INTRO_FASE, JUEGO, PAUSE, GAMEOVER};
	Estado estado;

	bool flags[GAMEOVER+1];
	//fase del juego
	int fase;

	//texto de la pantalla de inicio y nombre del jugador
	std::string inputText;
	int tama�o;
	SDL_Color textColor;
	bool renderText;
	Timer tiempo_fase, tiempo_ataques;

	//texto en el cambio de fase
	Texture texto_cambio, texto_nfase;
};
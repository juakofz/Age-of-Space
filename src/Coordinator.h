#pragma once
#include "Game.h"


class Coordinator
{
public:
	Coordinator(void);
	~Coordinator(void);

	void initGame();
	void mainEvent();
	bool event(SDL_Event *e);
	void actViewports();
	void render();

protected:
	Game game;

	//estados
	enum Estado {INICIO, INTRO_FASE, JUEGO, PAUSE, WIN, GAMEOVER};
	Estado estado;

	bool flags[GAMEOVER+1];
	//fase del juego
	int fase;

	//texto de la pantalla de inicio y nombre del jugador
	std::string inputText;
	int tamaño;
	SDL_Color textColor;
	bool renderText;
	Timer tiempo_fase, tiempo_ataques;

	//texto en el cambio de fase
	Texture texto_cambio, texto_nfase, texto_gameover, texto_gameover2, texto_pause, texto_pauseins, texto_inicioins, texto_win;
};


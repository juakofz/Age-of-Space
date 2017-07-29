#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Vector2.h"
//#include "Global.h"


extern const int g_SCREEN_WIDTH;
extern const int g_SCREEN_HEIGHT;
extern SDL_Renderer* g_Renderer;


class Texture
{

public:
	//Constructor
	Texture();
	//Destructor
	~Texture();

	//Cargar
	bool load(std::string path, SDL_Renderer* renderer = g_Renderer);
	bool loadText(std::string textureText, int tama�o, SDL_Color color, int fuente=1 );

	//Liberar
	void free();

	//Modulaci�n de color
	void setColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

	//Modo de blending
	void setBlendMode(SDL_BlendMode blending);

	//Alpha
	void setAlpha(Uint8 alpha);

	//texto a imagen
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

	//Renderizado
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renderizado por centro y rect
	void render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip = NULL, double angle  = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//renderizado por rectangulo de renderizado y posicion. no gira
	void render(SDL_Renderer* renderer, Vector2* Quad=NULL, int x=0, int y=0, SDL_Rect* clip = NULL);

	//Dimensiones
	Vector2 getDim();

	//Diagonal
	float getDiag();

private:

	//La propia textura
	SDL_Texture* texture;
	//Tama�o
	Vector2 dim;

	float diag;
};


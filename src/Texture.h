#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Vector2.h"

class Texture
{
public:
	//Constructor
	Texture();
	//Destructor
	~Texture();

	//Cargar
	bool load(std::string path, SDL_Renderer* renderer);

	//Liberar
	void free();

	//Modulación de color
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	//Modo de blending
	void setBlendMode(SDL_BlendMode blending);

	//Alpha
	void setAlpha(Uint8 alpha);

	//Renderizado por posición y textura
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Renderizado por centro y rect
	void render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip = NULL, double angle  = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Dimensiones
	Vector2 getDim();

	//Diagonal
	float getDiag();

private:
	//La propia textura
	SDL_Texture* texture;
	//Tamaño
	Vector2 dim;
	//Diagonal
	float diag;
};


//funciones y variables globales
#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

#include "Texture.h"
#include "LWindow.h"
#include "Mouse.h"


using namespace std;


class LWindow;

//Textura del texto
extern Texture gTextTexture;

//renderizado general
extern SDL_Renderer* gRenderer;

//Tamaño de la pantalla
extern Texture gSceneTexture;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Límite FPS
extern const int SCREEN_FPS;
extern const int SCREEN_TICKS_PER_FRAME;

//texto introducido por teclado
extern bool textinput(std::string *inputText, bool renderText, SDL_Event e);
extern void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño);
extern bool loadText();

extern Texture gPromptTextTexture;
extern Texture gInputTextTexture;

//Globally used font
extern TTF_Font *gFont;

//Starts up SDL and creates window
extern bool init();

//Frees media and shuts down SDL
extern void close();

//ventana del juego
extern LWindow gWindow;

extern struct characts;
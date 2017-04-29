//funciones y variables globales
#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Window.h"
#include "Mouse.h"


using namespace std;


class Window;

//Textura del texto
extern Texture g_TextTexture;

//renderizado general
extern SDL_Renderer* g_Renderer;

//Tamaño de la pantalla
extern Texture g_SceneTexture;
extern const int g_SCREEN_WIDTH;
extern const int g_SCREEN_HEIGHT;

//Límite FPS
extern const int SCREEN_FPS;
extern const int SCREEN_TICKS_PER_FRAME;

//texto introducido por teclado
extern bool textinput(std::string *inputText, bool renderText, SDL_Event e);
extern void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño);
extern bool loadText();

extern Texture g_PromptTextTexture;
extern Texture g_InputTextTexture;

//Object codes
//extern enum Items;

//Globally used font
extern TTF_Font * g_Font;

//Starts up SDL and creates window
extern bool init();

//Frees media and shuts down SDL
extern void close();

//ventana del juego
extern Window g_Window;

//extern struct characts;
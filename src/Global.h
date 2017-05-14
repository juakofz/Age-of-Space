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


extern SDL_Renderer* g_Renderer; //Global renderer
extern Window g_Window; //Game window
extern const int g_SCREEN_WIDTH; //Screen size
extern const int g_SCREEN_HEIGHT;
extern const Uint8 * g_keyboardState; //Keyboard state array

//Global flags
extern bool g_f_debug;
//...


extern Texture g_SceneTexture;
//FPS cap
extern const int SCREEN_FPS;
extern const int SCREEN_TICKS_PER_FRAME;

//texto introducido por teclado
extern bool textinput(std::string *inputText, bool renderText, SDL_Event e);
extern void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño);
extern bool loadText();
extern Texture g_PromptTextTexture;
extern Texture g_InputTextTexture;

//Globally used font
extern TTF_Font * g_Font;

//Starts up SDL and creates window
extern bool init();

//Frees media and shuts down SDL
extern void close();



//Areas
enum AREAS
{
	TOP_BAR = 0,
	GAME = 1,
	ORDERS = 2,
	INFO = 3,
	MAP = 4,
	WINDOW = 5,
	AREA_NUMBER = 6
};
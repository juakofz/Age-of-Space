#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <random>

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
extern Texture g_tex[15]; //Game textures

//Global flags
extern bool g_f_debug;

//Random number generation
extern random_device g_rd;
extern mt19937 g_mt;

extern float g_rand_float(float from, float to);
extern int g_rand_int(int from, int to);
extern SDL_Color g_rand_solidcolor();


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

enum SIZES
{
	SIZE_TINY = 10,
	SIZE_SMALL = 15,
	SIZE_MEDIUM = 20,
	SIZE_LARGE = 30,
	SIZE_HUGE = 50
};

enum OBJECT_TYPES
{
	ERROR = -1,
	NONE = 0,
	SHIP = 1,
	WEAPON_LASER = 10,
	WEAPON_MINILASER = 11,
};
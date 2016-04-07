

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>

#include <SDL_ttf.h>

#include "Texture.h"
#include "LWindow.h"

class LWindow;
extern Texture gTextTexture;
//SDL_Window* gWindow = NULL;
extern SDL_Renderer* gRenderer;

//Scene textures
extern Texture gSceneTexture;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Globally used font
extern TTF_Font *gFont;

//Starts up SDL and creates window
extern bool init();

//Loads media
extern bool loadMedia();

//Frees media and shuts down SDL
extern void close();

extern LWindow gWindow;

extern bool loadText();
#include "Global.h"

//SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Scene textures
Texture gSceneTexture;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LWindow gWindow;

//	, barraQuad, menuQuad, caractQuad;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		if( !gWindow.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = gWindow.createRenderer();
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	//Free loaded images
	gSceneTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	gWindow.free();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load scene texture
	if( !gSceneTexture.load("alquimiapre.png", gRenderer) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}

	return success;
}
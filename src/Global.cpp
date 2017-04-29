#include "Global.h"

//SDL_Window* gWindow = NULL;
SDL_Renderer* g_Renderer = NULL;

//Scene textures
Texture g_SceneTexture;

//tama�o de la pantalla
const int g_SCREEN_WIDTH = 960;
const int g_SCREEN_HEIGHT = 640;

//L�mite FPS
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Object codes
//const enum Items {
//	AST = 0,
//	NAVE = 1,
//	EDIF = 2,
//	PROY = 3,
//	EXPL = 4
//};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Handle and render text imput
bool textinput(std::string *inputText, bool renderText, SDL_Event e);
void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int size);
//Text textures
Texture g_PromptTextTexture;
Texture g_InputTextTexture;
Texture g_TextTexture;

//Globally used font
TTF_Font *g_Font = NULL;

//Main window
Window g_Window;


//Init SDL
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering. 0 for none, 1 for linear, 2 for anisotropic
		//Using 0 for pixelated effect
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Set mouse mode to relative
		//SDL_SetRelativeMouseMode(SDL_TRUE);

		//Create window
		if( !g_Window.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			g_Renderer = g_Window.createRenderer();
			if( g_Renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

//Free resources and close SDL
void close()
{
	//Free loaded images
	g_TextTexture.free();

	//Free global font
	TTF_CloseFont( g_Font );
	g_Font = NULL;

	//Destroy window	
	SDL_DestroyRenderer( g_Renderer );
	g_Window.free();
	g_Renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//Handle text imput
bool textinput(std::string *inputText, bool renderText, SDL_Event e)
{
	if( e.type == SDL_KEYDOWN )
	{
		//permite introducir texto
		SDL_StartTextInput();
		//Handle backspace
		if( e.key.keysym.sym == SDLK_BACKSPACE && inputText->length() > 0 )
		{
			//lop off character
			inputText->pop_back();
			renderText = true;
		}
		//Handle copy
		else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
		{
			SDL_SetClipboardText( inputText->c_str() );
		}

		//Handle paste
		//something here is wrong
		/*else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
		{
			inputText = SDL_GetClipboardText();
			renderText = true;
		}*/
	}
	//Special text input event
	else if( e.type == SDL_TEXTINPUT )
	{
		//Not copy or pasting
		if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
		{
			//Append character
			inputText->append(e.text.text);
			renderText = true;
		}
	}

	SDL_StopTextInput(); //stops keyboard imput
	return renderText; //true if it is to be rendered
}


//renderiza el texto
void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tama�o)
{
	if( renderText )
	{
		//Text is not empty
		if( inputText != "" )
		{
			//Render new text
			g_InputTextTexture.loadText( inputText.c_str(),tama�o, textColor );
		}
		//Text is empty
		else
		{
			//Render space texture
			g_InputTextTexture.loadText( " ", tama�o, textColor );
		}
	}
}
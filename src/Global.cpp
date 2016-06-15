#include "Global.h"

//SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Scene textures
Texture gSceneTexture;

//tamaño de la pantalla
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

//Límite FPS
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Object codes
const enum Items {
	AST = 0,
	NAVE = 1,
	EDIF = 2,
	PROY = 3,
	EXPL = 4
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//cargan el texto del reclado y lo renderizan
bool textinput(std::string *inputText, bool renderText, SDL_Event e);
void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño);

//texturas del texto
Texture gPromptTextTexture;
Texture gInputTextTexture;

//Globally used font
TTF_Font *gFont = NULL;

//ventana
LWindow gWindow;

//textura texto
Texture gTextTexture;



//inicializa
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
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Set mouse mode to relative
		//SDL_SetRelativeMouseMode(SDL_TRUE);

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

//cierra el programa
void close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	gWindow.free();
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

typedef struct characts
{
	Texture *tex;
	string name;
};

//texto por teclado
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
		//esta comentado porq me da un error
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
	//devuelve si hay que renderizar el texto
	return renderText;
	//cierra la comunicacion con el telclado
	SDL_StopTextInput();
}


//renderiza el texto
void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño)
{
	if( renderText )
	{
		//Text is not empty
		if( inputText != "" )
		{
			//Render new text
			gInputTextTexture.loadText( inputText.c_str(),tamaño, textColor );
		}
		//Text is empty
		else
		{
			//Render space texture
			gInputTextTexture.loadText( " ", tamaño, textColor );
		}
	}
}
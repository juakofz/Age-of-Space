#include "Global.h"


SDL_Renderer* g_Renderer = NULL; //Global renderer
Window g_Window; //Main window
const int g_SCREEN_WIDTH = 960; //Screen size
const int g_SCREEN_HEIGHT = 640;
const Uint8 * g_keyboardState = NULL; //Keyboard state array
Texture g_tex[15]; //Game textures

//Global flags
bool g_f_debug = false;

//Random number generation
random_device g_rd;
mt19937 g_mt(g_rd());

//Scene textures
Texture g_SceneTexture;

//Límite FPS
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

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


//Init SDL
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering. 0 for none, 1 for linear, 2 for anisotropic
		//Using 0 for pixelated effect
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Set mouse mode to relative. Hides system cursor and restricts it's movement to the current window
		SDL_SetRelativeMouseMode(SDL_TRUE);

		//Create window
		if(!g_Window.init())
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			g_Renderer = g_Window.createRenderer();
			if( g_Renderer == NULL )
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!( IMG_Init( imgFlags ) & imgFlags ))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				 //Initialize SDL_ttf
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
	TTF_CloseFont(g_Font);
	g_Font = NULL;

	//Destroy window	
	SDL_DestroyRenderer(g_Renderer);
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
	if(e.type == SDL_KEYDOWN)
	{
		//permite introducir texto
		SDL_StartTextInput();
		//Handle backspace
		if(e.key.keysym.sym == SDLK_BACKSPACE && inputText->length() > 0)
		{
			//lop off character
			inputText->pop_back();
			renderText = true;
		}
		//Handle copy
		else if(e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(inputText->c_str());
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


void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño)
{
	if( renderText )
	{
		//Text is not empty
		if( inputText != "" )
		{
			//Render new text
			g_InputTextTexture.loadText( inputText.c_str(),tamaño, textColor );
		}
		else
		{
			//Render space texture
			g_InputTextTexture.loadText( " ", tamaño, textColor );
		}
	}
}


//Random number generation
float g_rand_float(float from, float to)
{
	uniform_real_distribution<float> random(from, to);
	float aux = random(g_rd);
	return aux;
}

int g_rand_int(int from, int to)
{
	uniform_int_distribution<int> random(from, to);
	int aux = random(g_rd);
	return aux;
}

SDL_Color g_rand_solidcolor()
{
	uniform_int_distribution<int> random(0, 255);
	SDL_Color aux;
	aux.r = random(g_rd);
	aux.g = random(g_rd);
	aux.b = random(g_rd);
	aux.a = 255;
	return aux;
}
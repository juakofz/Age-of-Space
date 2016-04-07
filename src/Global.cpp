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

bool textinput(std::string *inputText, bool renderText, SDL_Event e);
void Textrender(std::string inputText, bool renderText, SDL_Color textColor, int tamaño);

Texture gPromptTextTexture;
Texture gInputTextTexture;

//Globally used font
TTF_Font *gFont = NULL;

LWindow gWindow;

Texture gTextTexture;

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

bool textinput(std::string *inputText, bool renderText, SDL_Event e)
{
	if( e.type == SDL_KEYDOWN )
					{
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
							//inputText += e.text.text;
							//strcat(inputText, e.text.text);
							inputText->append(e.text.text);
							renderText = true;
							//printf("inputtext");
						}
					}
	return renderText;
	SDL_StopTextInput();
}

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
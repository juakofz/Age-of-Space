#include "Texture.h"
#include <SDL_ttf.h>
#include "Global.h"

//Constructor
Texture::Texture()
{
	//Inicializar
	texture = NULL;
	dim.x = 0;
	dim.y = 0;
	diag=0;
}

//Destructor
Texture::~Texture()
{
	//Liberar textura
	free();
}

//Cargar imagen y control de errores
bool Texture::load(std::string path, SDL_Renderer* renderer)
{
	//Liberar posible textura anterior
	free();

	//Nueva textura
	SDL_Texture* newTexture = NULL;

	//Cargar imagen
	SDL_Surface* img = IMG_Load(path.c_str());
	if (img == NULL)
	{
		printf("Error al cargar la imagen %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color keying
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0xFF, 0xFF, 0xFF));

		//Crear la textura desde la imagen
		newTexture = SDL_CreateTextureFromSurface(renderer, img);
		if (newTexture == NULL)
		{
			printf("Error al crear la textura desde %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Utilizar diménsiones de la imagen
			dim.x = img->w;
			dim.y = img->h;
			diag = sqrt(dim.x * dim.x + dim.y * dim.y);
		}

		//Liberar imagen
		SDL_FreeSurface(img);
	}

	//Devolver éxito
	texture = newTexture;
	return texture != NULL; //(¿?)
}

//Liberar (tec)
void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		dim.x = 0;
		dim.y = 0;
	}
}

bool Texture::loadText(std::string textureText, int tamaño, SDL_Color textColor, int fuente)
{
	//Loading success flag
	bool success = true;

	
	//Open the font
	if(fuente==1) gFont = TTF_OpenFont( "img/SPACEBAR.ttf", tamaño );
	if(fuente==2) gFont = TTF_OpenFont( "img/fuente2.ttf", tamaño );	
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		if( !loadFromRenderedText( textureText.c_str(), textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

	return success;
}



//Modulación de color (tec)
void Texture::setColor(Uint8 r, Uint8 g, Uint8 b) 
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

//Modo de blending (tec)
void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture, blending);
}

//Alpha (tec)
void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}


bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			dim.x = textSurface->w;
			dim.y = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return texture != NULL;
}

//Renderizado
void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Espacio de renderizado
	SDL_Rect renderQuad = { x, y, dim.x, dim.y };

	//Espacio final de renderizado de renderizado
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Renderizado
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

//Renderizado por centro y rect
void Texture::render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip, double angle, SDL_RendererFlip flip)
{

	//Espacio de renderizado
	SDL_Rect renderQuad = { center->x -  w/2, center->y - h/2, w, h};

	//Porción renderizada de la textura
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Renderizado
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, NULL, flip);
}

//renderizado por rectangulo y posicion
void Texture::render(SDL_Renderer* renderer, Vector2* Quad, int x, int y, SDL_Rect* clip)
{
		
	//espacio final de renderizado
	SDL_Rect renderQuad;
	renderQuad.x=x;
	renderQuad.y=y;

	if(Quad!=NULL)
		{
			renderQuad.w = Quad->x;
			renderQuad.h = Quad->y;
		}
	/*else
		{
			renderQuad.w= dim.x;
			renderQuad.h= dim.y;
	}*/


	//Renderizado
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

//Dimensiones
Vector2 Texture::getDim() 
{
	return dim;
}

//Diagonal
float Texture::getDiag()
{
	return diag;
}


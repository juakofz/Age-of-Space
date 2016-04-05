#include "Texture.h"

//Constructor
Texture::Texture()
{
	//Inicializar
	texture = NULL;
	dim.x = 0;
	dim.y = 0;
	diag = 0;
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
		//Color keying (blanco)
		SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0xFF, 0xFF, 0xFF));

		//Crear la textura desde la imagen
		newTexture = SDL_CreateTextureFromSurface(renderer, img);
		if (newTexture == NULL)
		{
			printf("Error al crear la textura desde %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Utilizar dim�nsiones de la imagen
			dim.x = img->w;
			dim.y = img->h;
			diag = sqrt(dim.x * dim.x + dim.y * dim.y);
		}

		//Liberar imagen
		SDL_FreeSurface(img);
	}

	//Devolver �xito
	texture = newTexture;
	return texture != NULL; //(�?)
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

//Modulaci�n de color (tec)
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

//Renderizado por posici�n y textura
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

	//Espacio final de renderizado de renderizado
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Renderizado
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, NULL, flip);
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

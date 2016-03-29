#include "Texture.h"

//Constructor
Texture::Texture()
{
	//Inicializar
	texture = NULL;
	dim.x = 0;
	dim.y = 0;
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

//Dimensiones
Vector2 Texture::getDim() 
{
	return dim;
}

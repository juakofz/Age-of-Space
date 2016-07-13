#include "Button.h"


Button::Button(void)
{
	pos.x = 0;
	pos.y = 0;
}


Button::~Button(void)
{
}

//Sets top left position
void Button::setPos( int x, int y )
{
	pos.x = x;
	pos.y = y;
}

//Handles mouse event
bool Button::event( SDL_Event* e, SDL_Point xyrel )
{
	//If mouse event happened
	if(clickOn(e, xyrel))
	{	

		switch( e->button.button )
		{
			case SDL_BUTTON_LEFT:
			return 1;
			break;
			
			case SDL_BUTTON_RIGHT:
			break;
				
		}
	}
}
	
//Shows button sprite
void Button::render(Vector2 botondim)
{
	size=botondim;
	tex->render(gRenderer, &botondim, (int)pos.x,(int)pos.y);
	//Marcador de selección
	if (sel == true)
	{
		printf("marcador de seleccion\n");
	}
}

bool Button::clickOn(SDL_Event* e, SDL_Point xyrel) //faltan un par de cambios
{
	int mx=xyrel.x, my=xyrel.y;
	bool flag =false;

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Vector2 size = tex->getDim();
		if((((mx >= pos.x) && (mx <= (pos.x + size.x))) && ((my >= pos.y) && (my <= (pos.y + size.y))))) flag =true;
	}
	
	return flag;
}

void Button::setTexture(Texture *t)
{
	tex=t;

}
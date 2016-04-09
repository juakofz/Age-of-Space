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
void Button::event( SDL_Event* e )
{
	//If mouse event happened
	if(clickOn(e))
	{	
		switch( e->type )
		{
			case SDL_BUTTON_LEFT:
			printf("pulsado boton izquierdo sobre el boton");
			break;
			
			case SDL_BUTTON_RIGHT:
			printf("pulsado boton derecho sobre el boton");
			break;
				
		}
	}
}
	
//Shows button sprite
void Button::render()
{
	tex.render(gRenderer,(int)pos.x,(int)pos.y);

	//Marcador de selección
	if (sel == true)
	{
		//ya se vera
	}
}

bool Button::clickOn(SDL_Event* e) //faltan un par de cambios
{
	int mx, my;
	bool flag =false;

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//printf("click\n");
		Vector2 size = tex.getDim();
		SDL_GetMouseState(&mx, &my);

		if((((mx >= pos.x) && (mx <= (pos.x + size.x))) && ((my >= pos.y) && (my <= (pos.y + size.y))))) flag =true;
	}
	return flag;
}


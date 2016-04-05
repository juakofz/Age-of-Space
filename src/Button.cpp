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
			
			break;
			
			case SDL_BUTTON_RIGHT:
			
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
		SDL_Rect rec_sel;
		rec_sel.x = pos.x;
		rec_sel.y = pos.y;
		rec_sel.h = tex.getDim().x;
		rec_sel.w = tex.getDim().y;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);;
		SDL_RenderDrawRect(gRenderer, &rec_sel);
	}
}

bool Button::clickOn(SDL_Event* e)
{
	int mx, my;
	bool flag =false;

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		printf("click\n");
		Vector2 size = tex.getDim();
		SDL_GetMouseState(&mx, &my);

		if((((mx >= pos.x) && (mx <= (pos.x + size.x))) && ((my >= pos.y) && (my <= (pos.y + size.y))))) flag =true;
	}
	return flag;
}


#include "GameObject.h"

Texture * GameObject::tdisparo = 0;


GameObject::GameObject(void):type(-1)
{
	sel = false;
	sel_angle = 0;
	player = 0;

}

GameObject::GameObject( bool selec):type(-1)
{
	seleccionable = selec;
	if(seleccionable) player = 1;
	sel = false;
	sel_angle = 0;
}

GameObject::~GameObject(void)
{
	sel = false;
	sel_angle = 0;
}


int GameObject::event(SDL_Event* e,SDL_Rect selection, SDL_Point xyrel)
{
	return 0;
}

void GameObject::select()
{
	if(seleccionable)
	{
		sel = true;
		sel_angle = 0;
	}

}

void GameObject::deselect()
{
	if(seleccionable) sel = false;
}

//Renderizado
void GameObject::render(Camera cam)
{

	if (cam.isVisible(GetCen(), 20))
	{
		SDL_Point center;
		center.x = cen.x - cam.getPos().x;
		center.y = cen.y - cam.getPos().y;

	
		tex->render(gRenderer, &center, width, height, NULL, angle + 90);

		if(seleccionable)
		{
			SDL_Rect selection;
			selection.x = pos.x - size*0.1;
			selection.y = pos.y - size*0.1;
			selection.w = selection.h = size * 1.2;

			if (sel)
			{
				marker->render(gRenderer, &center, selection.w, selection.h, NULL, sel_angle);
				if (sel_angle > 360) sel_angle = 0;
				else sel_angle++;
			}
		}
	}
}


//Posici�n
Vector2 GameObject::GetPos()
{
	return pos;
}

void GameObject::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	cen.x = pos.x + tex->getDim().x / 2;
	cen.y = pos.y + tex->getDim().y / 2;
}


//Centro
Vector2 GameObject::GetCen()
{
	return cen;
}

Vector2& GameObject::getCen()
{
	return cen;
}

/*void GameObject::getCen(float &x, float &y)
{
	&x=&cen.x;
	&y=&cen.y;
}*/

//Cambia el centro y la posici�n
void GameObject::SetCen(float x, float y)
{
	cen.x = x;
	cen.y = y;
	pos.x = cen.x - tex->getDim().x / 2;
	pos.y = cen.y - tex->getDim().y / 2;
}

void GameObject::giveCen(Vector2 &dest)
{
	dest = cen;
}

//Asignaci�n de textura
void GameObject::SetTex(Texture *t)
{
	tex = t;
}

void GameObject::setMarker(Texture *t)
{
	marker = t;

}

bool GameObject::getSel()
{
	return sel;
}

bool GameObject::clickOn(SDL_Point mxy)
{
	if ((((mxy.x >= pos.x) && (mxy.x <= (pos.x + tex->getDim().x))) && ((mxy.y >= pos.y) && (mxy.y <= (pos.y + tex->getDim().y)))))  return true;
		
	else return false;
}

//Tama�o
void GameObject::setSize(int s)
{
	size = s;
	float scale = s / tex->getDiag();
	width = tex->getDim().x * scale;
	height = tex->getDim().y * scale;
}	

int GameObject::getSize()
{
	return size;
}

Vector2 GameObject::getDim()
{
	return tex->getDim();
}

int GameObject::getType()
{
	return type;
}


void GameObject::setTextures(Texture *tdisp)
{
	tdisparo = tdisp;
}

//Player
void GameObject::setPlayer(int p)
{
	player = p;
}

int GameObject::getPlayer()
{
	return player;
}

#include "ListaNaves.h"


ListaNaves::ListaNaves(void)
{
}


ListaNaves::~ListaNaves(void)
{

}

bool ListaNaves::agregar (Ship *nave) 
{ 
    lista.push_back(nave);    
    return true;    
} 

void ListaNaves::render(Camera cam) 
{ 
    for(int i = 0; i < lista.size(); i++)
	{
		lista[i]->move();
		lista[i]->render(cam);   
	}
	l_expl.render(cam);
} 

void ListaNaves::eliminarNave(int ind) 
{ 
    if((ind < 0)||(ind >= lista.size())) return;

	Explosion * e_aux = new Explosion(lista[ind]->getCen().x, lista[ind]->getCen().y, lista[ind]->getSize());
	l_expl.agregar(e_aux);

    delete lista[ind];    
    lista.erase(lista.begin()+ind);   

} 

void ListaNaves::eliminarContenido()
{
	for(int i = lista.size() - 1; i >= 0 ;i--)
	{
		delete lista[i];    
		lista.erase(lista.begin()+i);   
	}

}

void ListaNaves::eliminarJugador(int j)
{
	for(int i = lista.size() - 1; i >= 0 ;i--)
	{
		if(lista[i]->getPlayer() == j)
		{
			delete lista[i];    
			lista.erase(lista.begin()+i);   
		}
	}
}

int ListaNaves::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	int k = 0;
	for(int i = 0; i < lista.size(); i++)
	{
		if( lista[i]->event(e, selection, xyrel) )
		{
			k = 1;
			for(int j = 0; j < lista.size(); j++)
			{
				if(j != i)
				{
					if(lista[j]->clickOn(xyrel))
						{
							//Vector2 dest;
							//dest=lista[i]->getDest();
							//lista[i]->follow(lista[j]->getCen());
							//cout<<dest.x<<","<<dest.y<<endl;
							//lista[j]->giveCen(dest);
							//lista[j]->follow(centro);
					}
				}
			}
		}
	}

	return k;
}

bool ListaNaves::getSel(int ind)
{
	if(lista[ind]->getSel()) return true;
	else return false;
}

int ListaNaves::getSel()
{
	for(int i=0;i<lista.size();i++) if(getSel(i)) return i+1;
	return 0;
}

Vector2 ListaNaves::getCen(int i)
{
	return lista[i]->GetCen();
}

Vector2 ListaNaves::getPointyEnd(int i)
{
	return lista[i]->getPointyEnd();
}

int ListaNaves::getSels()
{
	int i=0;
	for(int j=0;j<lista.size();j++) if(getSel(j)) i++;
	return i;
}

int ListaNaves::getSize()
{
	return lista.size();
}

int ListaNaves::getPlayer(int ind)
{
	return lista[ind]->getPlayer();
}

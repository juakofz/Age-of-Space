#include "ListaNaves.h"


ListaNaves::ListaNaves(void)
{
}


ListaNaves::~ListaNaves(void)
{

}

bool ListaNaves::agregar (Ship *nave) 
{ 
	cout<<lista.size()<<endl;
    lista.push_back(nave);    
    return true;    
} 

void ListaNaves::render(Camera cam) 
{ 
    for(int i=0;i<lista.size();i++)
	{
		lista[i]->move();
		lista[i]->render(cam);   
	}
} 

void ListaNaves::eliminarNave(int ind) 
{ 
    if((ind<0)||(ind>=lista.size())) return;              
    delete lista[ind];    
    lista.erase(lista.begin()+ind);    
} 

int ListaNaves::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	int k=0;
	for(int i=0;i<lista.size();i++)
	{
		if( lista[i]->event(e, selection, xyrel) )
		{
			k=1;
			for(int j=0;j<lista.size();j++)
			{
				if(j!=i)
				{
					if(lista[j]->clickOn(xyrel))
						{
							Vector2 dest;
							dest=lista[i]->getDest();
							//lista[i]->follow(lista[j]->getCen());
							cout<<dest.x<<","<<dest.y<<endl;
							lista[j]->giveCen(dest);
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

bool ListaNaves::impactos(Proyectil p)
{
	for (int i=0;i<lista.size();i++)
	{
			if(lista[i]->disparada(p))
			{
				eliminarNave(i);
				return 1;
			}
	}
	return 0;
}


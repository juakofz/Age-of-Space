#include "ListaProyectiles.h"


ListaProyectiles::ListaProyectiles(void)
{
}


ListaProyectiles::~ListaProyectiles(void)
{
	for(int i=0;i<lista.size();i++) 
	{
		delete lista[i];
		lista [i]=0;
	}
}

bool ListaProyectiles::agregar (Proyectil *ast) 
{ 
    lista.push_back(ast);    
    return true;    
} 

void ListaProyectiles::render(Camera cam) 
{ 
    for(int i=0;i<lista.size();i++)
	{
		if (cam.isVisible(lista[i]->GetCen(), 20))
		{
			lista[i]->render(cam);
		}       
	}
} 

void ListaProyectiles::eliminarProyectil(int ind) 
{ 
    if((ind<0)||(ind>=lista.size())) return;              
    delete lista[ind];    
    lista.erase(lista.begin()+ind);    
} 

void ListaProyectiles::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	for(int i=0;i<lista.size();i++) lista[i]->event(e, selection, xyrel);
}

bool ListaProyectiles::getSel(int ind)
{
	if(lista[ind]->getSel()) return true;
	else return false;
}

int ListaProyectiles::getSel()
{
	for(int i=0;i<lista.size();i++) if(getSel(i)) return i+1;
	return 0;
}

void ListaProyectiles::impacto(ListaNaves l)
{
	for(int i=0;i<lista.size();i++)
	{
		if(l.impactos(*lista[i])) 
		{
			eliminarProyectil(i);
		}
	}
}
#include "ListaObjetos.h"


ListaObjetos::ListaObjetos(void)
{
}


ListaObjetos::~ListaObjetos(void)
{
}

bool ListaObjetos::agregar(GameObject *elemento) 
{ 
    lista.push_back(elemento);    
    return true;    
} 

void ListaObjetos::render(Camera cam) 
{ 
     for(int i=0;i<lista.size();i++)
	{
			lista[i]->render(cam);      
	}
} 


int ListaObjetos::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	for(int i=0;i<lista.size();i++) return lista[i]->event(e, selection, xyrel);
}

bool ListaObjetos::getSel(int ind)
{
	if(lista[ind]->getSel()) return true;
	else return false;
}

int ListaObjetos::getSel()
{
	for(int i=0;i<lista.size();i++) if(getSel(i)) return i+1;
	return 0;
}
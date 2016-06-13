#include "ListaEdificios.h"


ListaEdificios::ListaEdificios(void)
{
}


ListaEdificios::~ListaEdificios(void)
{
}

bool ListaEdificios::agregar (Edificio *edif) 
{ 
    lista.push_back(edif);    
    return true;    
} 

void ListaEdificios::render(Camera cam) 
{ 
    for(int i=0;i<lista.size();i++)
	{
		if (cam.isVisible(lista[i]->GetCen(), 20))
		{
			lista[i]->render(cam);
		}       
	}
} 

void ListaEdificios::eliminarEdificio(int ind) 
{ 
    if((ind<0)||(ind>=lista.size())) return;              
    delete lista[ind];    
    lista.erase(lista.begin()+ind);    
} 

void ListaEdificios::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	for(int i=0;i<lista.size();i++) lista[i]->event(e, selection, xyrel);
}

bool ListaEdificios::getSel(int ind)
{
	if(lista[ind]->getSel()) return true;
	else return false;
}

int ListaEdificios::getSel()
{
	for(int i=0;i<lista.size();i++) if(getSel(i)) return i+1;
	return 0;
}
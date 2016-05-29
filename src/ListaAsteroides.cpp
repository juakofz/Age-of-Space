#include "ListaAsteroides.h"


ListaAsteroides::ListaAsteroides(void)
{
        
}


ListaAsteroides::~ListaAsteroides(void)
{
}

bool ListaAsteroides::agregar (Asteroid *ast) 
{ 
    lista.push_back(ast);    
    return true;    
} 

void ListaAsteroides::render(Camera cam) 
{ 
    for(int i=0;i<lista.size();i++)
	{
		if (cam.isVisible(lista[i]->GetCen(), 20))
		{
			lista[i]->render(cam);
		}       
	}
} 

void ListaAsteroides::eliminarAsteroide(int ind) 
{ 
    if((ind<0)||(ind>=lista.size())) return;              
    delete lista[ind];    
    lista.erase(lista.begin()+ind);    
} 

void ListaAsteroides::event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel)
{
	for(int i=0;i<lista.size();i++) lista[i]->event(e, selection, xyrel);
}

bool ListaAsteroides::getSel(int ind)
{
	if(lista[ind]->getSel()) return true;
	else return false;
}

int ListaAsteroides::getSel()
{
	for(int i=0;i<lista.size();i++) if(getSel(i)) return i+1;
	return 0;
}
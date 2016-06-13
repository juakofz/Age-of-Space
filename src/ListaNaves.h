<<<<<<< HEAD
#pragma once


#include <vector>
#include "Ship.h"
#include "Camera.h"
#include "Proyectil.h"
#include "ListaExplosiones.h"



class ListaNaves

{
	friend class Interacciones;
	std::vector<Ship*> lista;

public:

	ListaNaves(void);
	~ListaNaves(void);

	bool agregar(Ship *nave);
	void render(Camera cam);
	void eliminarNave(int ind);
	int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	Vector2 getPointyEnd(int i);
	int getSel();
	int getSels();
	Vector2 getCen(int i);

	bool impactos(Proyectil p);

private:
	ListaExplosiones l_expl;
};



=======
#pragma once


#include <vector>
#include "Ship.h"
#include "Camera.h"
#include "Proyectil.h"




class ListaNaves

{
	friend class Interacciones;
	std::vector<Ship*> lista;

public:

	ListaNaves(void);
	~ListaNaves(void);

	bool agregar(Ship *nave);
	void render(Camera cam);
	void eliminarNave(int ind);
	int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);
	bool getSel(int ind);
	Vector2 getPointyEnd(int i);
	int getSel();
	int getSels();
	Vector2 getCen(int i);

	bool impactos(Proyectil p);
};



>>>>>>> refs/heads/pr/10

#pragma once
#include "T_Vector.h"
#include "Explosion.h"
#include "ProjectileVector.h"
#include "ShipVector.h"

#include "Quadtree.h"
#include "Interactions.h"
#include "RequestList.h"

#include "Camera.h"

class ObjectManager
{
public:

	~ObjectManager();


	//Singleton
	static ObjectManager * s_instance;

	static ObjectManager * getInstance()
	{
		if (!s_instance)
			s_instance = new ObjectManager;
		return s_instance;
	};

	//General
	void handleRequests(); //Handle object creation requests
	void update(); //Update manager
	void deleteOne(); //Delete one selected object
	void kill(); //Remove dead objects from vectors

	//Projectiles
	void createProjectile(int type, int player, Vector2 origin, Vector2 dest);

	//Explosions
	void createExplosion(int x, int y, int size);
	void updateExplosions();

	//Ships
	void createShip(int type, int player, Vector2 center);
	void shipEvents(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);
	void move();
	void render(Camera cam);

	//Interactions
	static bool collision(Vector2 cen1, float rad1, Vector2 cen2, float rad2);
	static bool collision(GameObject * obj1, GameObject * obj2);
	void projectileImpacts();
	void shipOverlap();
	void shipRepel(GameObject * s1, GameObject * s2);

	//Minimap rendering
	void renderMinimap();

private:

	ObjectManager();
	ObjectManager(ShipVector * ships, ProjectileVector * projectiles, T_Vector<Explosion> * explosions);

	RequestList * v_requests;
	Request m_request;

	Quadtree qt_overlap, qt_interactions;

	T_Vector<Explosion> * v_explosions;
	ObjectVector * v_objects;
	vector<ObjectVector> vv_quadvectors;				
	
};


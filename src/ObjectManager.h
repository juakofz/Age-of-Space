#pragma once
#include "ProjectileVector.h"
#include "ExplosionVector.h"
#include "ShipVector.h"

#include "Interactions.h"

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


	//Projectiles
	void createProjectile(int type, int player, Vector2 origin, Vector2 dest);
	//static Projectile * createProjectile(Station * station);
	void moveProjectiles();
	void renderProjectiles(Camera cam);

	//Explosions
	void createExplosion(int x, int y, int size);
	void updateExplosions();

	//Ships
	void createShip(int type, int player, Vector2 center);
	void shipEvents(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel);
	void moveShips();
	void renderShips(Camera cam);

	//Interactions
	static bool collision(Vector2 cen1, float rad1, Vector2 cen2, float rad2);
	void projectileImpacts();
	void shipOverlap();

	//Minimap rendering
	void renderMinimap();

private:

	ObjectManager();
	ObjectManager(ShipVector * ships, ProjectileVector * projectiles, ExplosionVector * explosions);

	ProjectileVector * v_projectiles;
	ExplosionVector * v_explosions;
	ShipVector * v_ships;
};


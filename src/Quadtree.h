#pragma once
#include "Vector2.h"
#include "T_Vector.h"
#include "ObjectVector.h"

class Quadtree
{
public:

	Quadtree();
	Quadtree(int level, SDL_Rect quad);
	~Quadtree();

	
	void clear(); //Clears current level and sublevels
	void split(); //Splits quadtree into its next level
	void add(GameObject * obj); //Add object to vector
	bool * locate(GameObject * obj, bool * loc); //Checks in which subquads is a given object
	int generate(ObjectVector * vector); //Generates quadtree from object vector
	vector<ObjectVector> retrieve(); //Retrieve the quadtrees object lists

	void render_debug(Camera cam); //+test+

private:

	int m_max_objects;
	int m_max_depth;
	
	int m_level;
	bool f_dead_end;
	SDL_Rect m_quad;

	Quadtree * m_nodes[4];
	ObjectVector v_objects;
	vector<SDL_Rect> v_rects;

};

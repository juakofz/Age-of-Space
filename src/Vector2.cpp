#include "Vector2.h"


//Constructor
Vector2::Vector2(float px, float py)
{
	x=px;
	y=py;
}

//Destructor
Vector2::~Vector2()
{
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
//SDL_Point

>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/development
SDL_Point Vector2::convert_int()
{
	SDL_Point ret;
	ret.x = x;
	ret.y = y;

	return ret;
}
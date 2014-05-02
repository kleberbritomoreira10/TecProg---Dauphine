#ifndef INCLUDE_COLLISION_H
#define INCLUDE_COLLISION_H

#include "SDLWrapper.h"

class Collision {

	public:
		static bool checkCollision(SDL_Rect& a, SDL_Rect& b);

};


#endif // INCLUDE_COLLISION_H
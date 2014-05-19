#ifndef INCLUDE_COLLISION_H
#define INCLUDE_COLLISION_H

#include "SDLWrapper.h"
#include "Entity.h"

/**
* For now, has simple collision detection.
*/
class Collision {

	public:
		/**
		* @return Whether two SDL_Rects collided.
		* @param a_ , b_ : The rectangles to check.
		*/
		static bool rectsCollided(const SDL_Rect& a_, const SDL_Rect& b_);

		static bool Environment(Entity* a_, const SDL_Rect& _b);
};


#endif // INCLUDE_COLLISION_H

#ifndef INCLUDE_COLLISION_H
#define INCLUDE_COLLISION_H

#include "SDLWrapper.h"
#include "Entity.h"

/**
* For now, has simple collision detection.
*/
class Collision {

	public:
		enum RectangleSide : uint8_t {
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NONE
		};

		/**
		* @return Whether two SDL_Rects collided.
		* @param a_ , b_ : The rectangles to check.
		*/
		static bool rectsCollided(const SDL_Rect& a_, const SDL_Rect& b_);

		/**
		*
		*/
		static bool environmentCollided(Entity* const a_, const SDL_Rect& b_);

		static RectangleSide rectsCollidedSide(const SDL_Rect& a_, const SDL_Rect& b_);

};

#endif // INCLUDE_COLLISION_H

#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "SDLWrapper.h"
#include "Sprite.h"
#include "Player.h"
#include "Camera.h"
#include "State.h"

/**
* Abstract class for levels.
* Contains background, player and a camera.
*/
class Level : public State {
	
	public:	
		
		/**
		* The destructor.
		* Resets all attributes.
		*/
		virtual ~Level();

		/**
		* @return The Level width.
		*/
		unsigned int getWidth();

		/**
		* @return The Level height.
		*/
		unsigned int getHeight();

		/**
		* @return The Level Player.
		*/
		Player* getPlayer();

	protected:

		/**
		* The constructor.
		*
		*/
		Level();

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player *player_) = 0;

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		virtual void setCamera(Camera *camera_) = 0;

		Sprite *background; /**< The levels background sprite. */

		unsigned int width; /**< Width that defines the horizontal limits. */
		unsigned int height; /**< Height that defines the vertical limits. */

		Player *player; /**< The direct reference to player, even though its in the list. */
		Camera *camera; /**< The current camera for that Level. */

};

#endif //INCLUDE_LEVEL_H

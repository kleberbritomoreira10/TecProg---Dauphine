#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "SDLWrapper.h"
#include "Sprite.h"
#include "Player.h"
#include "Camera.h"

/**
* Abstract class for levels.
* Contains background, player and a camera.
*/
class Level {
	
	public:
		
		/**
		* The destructor.
		* Resets all attributes.
		*/
		virtual ~Level();

		/**
		* Renders the level.
		* Always render on 0,0 position.
		* @param clip_ : Clips the texture, on the SDL_Rect bounds.
		* @see Sprite::render()
		*/
		virtual void render(SDL_Rect &clip_) = 0;

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player &player_) = 0;

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		virtual void setCamera(Camera &camera_) = 0;

		/**
		* @return The Level width.
		*/
		unsigned int getWidth();

		/**
		* @return The Level height.
		*/
		unsigned int getHeight();

	protected:
		/**
		* The constructor.
		* Defines the levels width and height limits.
		* @param background_ : Sets the background sprite, which defines the levels width and height.
		* @todo Probably isn't the best practice to make the background define the width/height. We might not want a background sprite later.
		*/
		Level(Sprite *background_);

		Sprite *background; /**< The levels background sprite. */

		unsigned int width; /**< Width that defines the horizontal limits. */
		unsigned int height; /**< Height that defines the vertical limits. */

		Player *player; /**< The direct reference to player, even though its in the list. */
		Camera *camera; /**< The current camera for that Level. */

};

#endif //INCLUDE_LEVEL_H

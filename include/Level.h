#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "Sprite.h"
#include "SDLWrapper.h"
#include "Player.h"
#include "Camera.h"

/**
* Represents the current level.
* Contains background, player and a camera. Should contain all(?) game objects related to that level in the future.
*/
class Level {
	
	public:
		/**
		* The constructor.
		* Defines the levels width and height limits.
		* @param width_ : Desired horizontal limit.
		* @param height_ : Desired vertical limit.
		*/
		Level(unsigned int width_, unsigned int height_);

		/**
		* The destructor.
		* Resets all attributes.
		*/
		~Level();

		/**
		*
		*
		*/
		void update();

		/**
		* Renders the level.
		* 
		* @param clip_ : Clips the texture, on the SDL_Rect bounds.
		* @see Sprite::render()
		*/
		void render(SDL_Rect *clip_);

		/**
		* @return The Level width.
		*/
		unsigned int getWidth();

		/**
		* @return The Level height.
		*/
		unsigned int getHeight();

		/**
		* @param player_ : Sets the player for the level.
		*/
		void setPlayer(Player &player_);

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		void setCamera(Camera &camera_);

		/**
		* @param background_ : Sets the background sprite for the level.
		*/
		void setBackground(Sprite *background_);

	private:
		unsigned int width; /**< Width that defines the horizontal limits. */
		unsigned int height; /**< Height that defines the vertical limits. */

		// Objects levelObjects[]
		Player *player; /**< The player instance in that Level. */
		Camera *camera; /**< The current camera for that Level. */
		Sprite *background; /**< The levels background sprite. */

};

#endif //INCLUDE_LEVEL_H

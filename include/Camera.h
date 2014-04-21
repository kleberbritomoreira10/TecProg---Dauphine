#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "SDLWrapper.h"

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		Camera();

		/**
		* The destructor.
		* 
		*/
		~Camera();

		/**
		* Updates the camera clip.
		* Centralizes the player on the screen.
		*/
		void update();

		/**
		* @return The camera clip (an SDL_Rect).
		*/
		SDL_Rect& getClip();

		/**
		* @param x_, y_ : Tells the camera what are the current (x,y) position of the player.
		* @see Level::update()
		*/
		void setPlayerXY(double x_, double y_);

		/**
		* @param width_, height_ : Tells the camera what are the current width and height of
		* 	the player.
		* @see Level::update()
		*/
		void setPlayerWH(unsigned int width_, unsigned int height_);

		/**
		* @param width_,height_ : Tells the camera what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(unsigned int width_, unsigned int height_);

	private:
		double playerX; /**< The current x position of the player. */
		double playerY; /**< The current y position of the player. */
		unsigned int playerW; /**< The current width of the player. */
		unsigned int playerH; /**< The current height of the player. */
		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		SDL_Rect clip; /**< Clip which will be used to clip the rendering only to the extent of
			the camera. */

};

#endif //INCLUDE_CAMERA_H

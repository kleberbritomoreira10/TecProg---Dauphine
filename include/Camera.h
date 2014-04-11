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
		* Resets all the attributes.
		*/
		~Camera();

		/**
		* Updates the camera clip.
		* Centralizes the player on the screen.
		*/
		void update();

		/**
		* @param x_,y_ : Sets the cameras knowledge of the players x,y position.
		* @see Level::update()
		*/
		void setPlayerXY(double x_, double y_);

		/**
		* @param width_,height_ : Sets the cameras knowledge of the players width,height.
		* @see Level::update()
		*/
		void setPlayerWH(unsigned int width_, unsigned int height_);

		/**
		* @param width_,height_ : Sets the cameras knowledge of the level width,height.
		* @see Level::update()
		*/
		void setLevelWH(unsigned int width_, unsigned int height_);

		SDL_Rect clip; /**< Clip which will be used to clip the rendering only to the extent of the camera. */

	private:
		double playerX;
		double playerY;
		unsigned int playerW;
		unsigned int playerH;
		unsigned int levelW;
		unsigned int levelH;

};

#endif //INCLUDE_CAMERA_H

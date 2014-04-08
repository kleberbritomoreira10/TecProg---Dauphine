#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Entity.h"
#include "Sprite.h"
#include "InputKeys.h"

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera : public Entity {

	public:
		/**
		* The constructor.
		* Creates the camera by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Camera(double x_, double y_, Sprite *sprite_);

		/**
		* The destructor.
		* Resets the attributes.
		*/
		virtual ~Camera();

		/**
		* Updates the camera.
		* Modifies whatever is necessary, relative to the camera.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent of processing speed.
		*/
		virtual void update(double dt_);

		/**
		* Renders the camera.
		* Uses the camera's sprite render method.
		* @see Sprite::render()
		*/
		virtual void render();

		/**
		* Updates the camera depending on recieved input.
		* Modifies whatever is necessary, relative to the camera.
		* @param keyState_ : The input handled boolean array that says which keys are pressed.
		*/
		void updateInput(bool keyState_[GK_MAX]);

		double vx; /**< The camera's speed on the x axis. */
		double vy; /**< The camera's speed on the x axis. */
		double speed; /**< Speed that moves camera on input. */
		SDL_Rect clip;

		bool canMove;
		bool canMovePlayer;
		bool getCanMove();

};

#endif //INCLUDE_CAMERA_H

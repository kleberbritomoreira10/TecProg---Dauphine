#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Entity.h"
#include "Sprite.h"

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public Entity {

	public:
		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Player(double x_, double y_, Sprite *sprite_);

		/**
		* The destructor.
		* Sets the x,y position to 0 and removes the Sprite.
		*/
		~Player();

		/**
		* Updates the player.
		* Modifies whatever is necessary, relative to the player.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		* @param keyState_ : The input handled boolean array that says which keys are pressed.
		*/
		void update(double dt_, bool keyState_[GK_MAX]);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render()
		*/
		void render();

		double vx; /**< The player's speed on the x axis. */
		double vy; /**< The player's speed on the x axis. */
		double speed; /**< Speed that moves player on input. */

};

#endif //INCLUDE_PLAYER_H

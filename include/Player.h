#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Entity.h"

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public Entity {

	public:
		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param lX : position in x axis.
		* @param lY : position in y axis.
		* @param lSprite : which sprite to use.
		*/
		Player(int lX, int lY, Sprite *lSprite);

		/**
		* The destructor.
		* Sets the x,y position to 0 and removes the Sprite.
		*/
		~Player();

		/**
		* Updates the player.
		* Modifies whatever is necessary, relative to the player.
		* @param dt : Delta time. Time elapsed between one frame and the other.
		*/
		void update(double dt, int velX, int velY);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render()
		*/
		void render();

};

#endif //INCLUDE_PLAYER_H

#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Entity.h"

class Player : public Entity {

	public:
		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @params lX : position in x axis.
		* @params lY : position in y axis.
		* @params lSprite : which sprite to use.
		*/
		Player(double lX, double lY, Sprite *lSprite);

		/**
		* The destructor.
		* Deallocates everything necessary.
		*/
		~Player();

		/**
		* Updates player.
		* Modifies whatever is necessary, relative to the player.
		* @params dt : Delta time. Time elapsed between one frame and the other.
		*/
		void update(double dt);

		/**
		* Renders player.
		* Uses the players sprite render method.
		*/
		void render();

};

#endif //INCLUDE_PLAYER_H

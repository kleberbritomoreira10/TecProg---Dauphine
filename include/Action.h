#ifndef INCLUDE_ACTION_H
#define INCLUDE_ACTION_H

#include "Sprite.h"
#include "Player.h"
#include "GameState.h"

class Player;

/**
* Abstract class for levels.
* Contains a background, player and a camera.
*/
class Action : public GameState {
	
	public:	
		/**
		* The destructor.
		* Deletes all the allocated attributes, even though the specific levels should.
		*/
		virtual ~Action();

		/**
		* @return The Level Player.
		*/
		Player* getPlayer();

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player* player_) = 0;

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		Action();

		Sprite* sprite; /**< The Action sprite. */
		Player* player; /**< The direct reference to player. */

};

#endif //INCLUDE_ACTION_H

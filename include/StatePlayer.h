#ifndef INCLUDE_PLAYERSTATE_H
#define INCLUDE_PLAYERSTATE_H

#include "Player.h"
#include "InputKeys.h"

#include <array>
using std::array;

class Player;

/**
* Parent class for other player states.
* 
*/
class StatePlayer {

	public:
		/**
		* The destructor.
		*/
		virtual ~StatePlayer(){}

		/**
		* Method called on load.
		* Pure virtual function. Called on state enter.
		*/
		virtual void enter() = 0;

		/**
		* Method called on unload.
		* Pure virtual function. Called on state exit.
		*/
		virtual void exit() = 0;

		/**
		* Update method for the state.
		* While the Player is on the state, this method runs every update.
		* @param keyStates_ : Boolean array that contains all input data.
		*/
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_) = 0;

		Player* player; /**< Reference to the player. */

};

#endif // INCLUDE_PLAYERSTATE_H
#ifndef INCLUDE_PSTATESETUPTRAP_H
#define INCLUDE_PSTATESETUPTRAP_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateSetUpTrap : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateSetUpTrap(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateSetUpTrap(){}

		/**
		* @see StatePlayer::enter
		*/
		virtual void enter();

		/**
		* @see StatePlayer::exit
		*/
		virtual void exit();

		/**
		* @see StatePlayer::handleInput
		*/
		virtual void handleInput(const std::array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATESETUPTRAP_H

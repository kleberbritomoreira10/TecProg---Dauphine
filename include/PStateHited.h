#ifndef INCLUDE_PSTATEHITED_H
#define INCLUDE_PSTATEHITED_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateHited : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateHited(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateHited(){}

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

#endif // INCLUDE_PSTATEHITED_H

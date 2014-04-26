#ifndef INCLUDE_PSTATEAERIAL_H
#define INCLUDE_PSTATEAERIAL_H

#include "StatePlayer.h"

/**
* The state for when the player is not grounded.
* 
*/
class PStateAerial : public StatePlayer {

	public:
		/**
		* The constructor.
		*/
		PStateAerial(){}

		/**
		* The destructor.
		*/
		virtual ~PStateAerial(){}

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
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEAERIAL_H

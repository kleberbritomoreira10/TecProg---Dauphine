#ifndef INCLUDE_PSTATEAERIAL_H
#define INCLUDE_PSTATEAERIAL_H

#include "PlayerState.h"

class PStateAerial : public PlayerState {

	public:

		PStateAerial(){}
		virtual ~PStateAerial(){}

		virtual void enter();
		virtual void exit();
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEAERIAL_H

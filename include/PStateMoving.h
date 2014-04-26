#ifndef INCLUDE_PSTATEMOVING_H
#define INCLUDE_PSTATEMOVING_H

#include "PlayerState.h"

class PStateMoving : public PlayerState {

	public:

		PStateMoving(){}
		virtual ~PStateMoving(){}

		virtual void enter();
		virtual void exit();
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEMOVING_H

#ifndef INCLUDE_PSTATEROLLING_H
#define INCLUDE_PSTATEROLLING_H

#include "PlayerState.h"

class PStateRolling : public PlayerState {

	public:

		PStateRolling(){}
		virtual ~PStateRolling(){}

		virtual void enter();
		virtual void exit();
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEROLLING_H

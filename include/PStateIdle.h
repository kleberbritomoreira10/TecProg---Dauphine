#ifndef INCLUDE_PSTATEIDLE_H
#define INCLUDE_PSTATEIDLE_H

#include "PlayerState.h"

class PStateIdle : public PlayerState {

	public:

		PStateIdle(){}
		virtual ~PStateIdle(){}

		virtual void enter();
		virtual void exit();
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEIDLE_H

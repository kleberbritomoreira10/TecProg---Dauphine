#ifndef INCLUDE_PLAYERSTATE_H
#define INCLUDE_PLAYERSTATE_H

#include "Player.h"
#include "InputKeys.h"

#include <array>
using std::array;

class Player;

class PlayerState {

	public:
		virtual ~PlayerState(){}
		virtual void enter() = 0;
		virtual void exit() = 0;
		virtual void handleInput(const array<bool, GameKeys::MAX> keyStates_) = 0;

		Player* player;

};

#endif // INCLUDE_PLAYERSTATE_H
#include "PStateAerial.h"
#include "Logger.h"

void PStateAerial::enter(){

}

void PStateAerial::exit(){

}

void PStateAerial::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Idle
    if(this->player->isGrounded){
    	this->player->changeState((*Player::stateIdle));
    	return;
    }

	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

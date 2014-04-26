#include "PStateAerial.h"
#include "Logger.h"

void PStateAerial::enter(){
	Logger::verbose("enter-> AERIAL");
}

void PStateAerial::exit(){

}

void PStateAerial::handleInput(const array<bool, GameKeys::MAX> keyStates_){

	// Idle
    if(this->player->isGrounded){
    	this->player->changeState((*Player::actionIdle));
    	return;
    }

	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

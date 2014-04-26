#include "PStateRolling.h"
#include "Logger.h"

void PStateRolling::enter(){
	Logger::verbose("enter-> ROLL");
	this->player->roll();
}

void PStateRolling::exit(){

}

void PStateRolling::handleInput(const array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		this->player->changeState((*Player::actionAerial));
		return;
	}

    this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::UP] && this->player->isGrounded){
		this->player->jump();
		this->player->changeState((*Player::actionAerial));
		return;
	}

	// Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState((*Player::actionIdle));
        return;
    }
}

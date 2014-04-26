#include "PStateIdle.h"
#include "Logger.h"

void PStateIdle::enter(){
	Logger::verbose("enter-> IDLE");
}

void PStateIdle::exit(){

}

void PStateIdle::handleInput(const array<bool, GameKeys::MAX> keyStates_){

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

	// Move
	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		this->player->changeState((*Player::actionMoving));
		return;
	}

	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState((*Player::actionRolling));
		return;
	}

}

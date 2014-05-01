#include "PStateIdle.h"
#include "Logger.h"

void PStateIdle::enter(){
	Logger::verbose("enter-> IDLE");
}

void PStateIdle::exit(){
	Logger::verbose("exit-> IDLE");
}

void PStateIdle::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		this->player->changeState((*Player::stateAerial));
		return;
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::UP] && this->player->isGrounded){
		this->player->jump();
		this->player->changeState((*Player::stateAerial));
		return;
	}

	// Move
	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		this->player->changeState((*Player::stateMoving));
		return;
	}

	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState((*Player::stateRolling));
		return;
	}

}

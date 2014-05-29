#include "PStateCrouching.h"
#include "Logger.h"

void PStateCrouching::enter(){
	this->player->isGrounded = true;
	this->player->maxSpeed /= 2;
	this->player->speed = 15;
}

void PStateCrouching::exit(){
	this->player->maxSpeed *= 2;
	this->player->speed = 20;
}

void PStateCrouching::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	if(!keyStates_[GameKeys::LCTRL]){
		this->player->changeState(Player::PStates::IDLE);
		return;
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		this->player->jump();
		this->player->isGrounded = false;
		return;
	}

	this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState(Player::PStates::ROLLING);
		return;
	}

}

PStateCrouching::PStateCrouching(Player* const player_) :
	StatePlayer(player_)
{
	
}

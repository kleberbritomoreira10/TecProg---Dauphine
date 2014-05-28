#include "PStateCrouch.h"
#include "Logger.h"

void PStateCrouch::enter(){
	Logger::verbose("::CROUCH");
	this->player->isGrounded = true;
	this->player->maxSpeed /= 2;
	this->player->speed = 15;
}

void PStateCrouch::exit(){
	this->player->maxSpeed *= 2;
	this->player->speed = 20;
}

void PStateCrouch::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	if(!keyStates_[GameKeys::DOWN]){
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

PStateCrouch::PStateCrouch(Player* const player_) :
	StatePlayer(player_)
{
	
}

#include "PStateIdle.h"
#include "Logger.h"

void PStateIdle::enter(){
	Logger::verbose("::IDLE");
	this->player->getAnimation()->changeAnimation(1,0,1,false,0);
	this->player->isGrounded = true;
}

void PStateIdle::exit(){

}

void PStateIdle::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		this->player->jump();
		this->player->isGrounded = false;
		return;
	}

	// Crouch
	if(keyStates_[GameKeys::DOWN]){
		this->player->changeState(Player::PStates::CROUCH);
		return;
	}

	// Move
	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		this->player->changeState(Player::PStates::MOVING);
		return;
	}

	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState(Player::PStates::ROLLING);
		return;
	}

}

PStateIdle::PStateIdle(Player* const player_) :
	StatePlayer(player_)
{

}

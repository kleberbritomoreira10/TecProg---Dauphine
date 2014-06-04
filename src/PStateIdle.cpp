#include "PStateIdle.h"
#include "Logger.h"

void PStateIdle::enter(){
	this->box.x = (int)this->player->getWidth() / 4;
	this->box.y = (int)this->player->getHeight() / 3.5;
	this->box.w = (int)this->player->getWidth() / 2;
	this->box.h = (int)this->player->getHeight() / 3.5;

	this->player->getAnimation()->changeAnimation(0, 0, 26, false, 2.6);
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
	if(keyStates_[GameKeys::CROUCH]){
		this->player->changeState(Player::PStates::CROUCHING);
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

	if(keyStates_[GameKeys::AIM]){
		this->player->changeState(Player::PStates::AIMING);
		return;
	}

}

PStateIdle::PStateIdle(Player* const player_) :
	StatePlayer(player_)
{

}

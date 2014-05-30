#include "PStateRolling.h"
#include "Logger.h"

void PStateRolling::enter(){
	this->player->getAnimation()->changeAnimation(6,4,9,true,0.6);
	this->player->roll();
}

void PStateRolling::exit(){

}

void PStateRolling::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

    this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE] && this->player->isGrounded){
		this->player->jump();
		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

	// Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState(Player::PStates::IDLE);
        return;
    }
}

PStateRolling::PStateRolling(Player* const player_) :
    StatePlayer(player_)
{

}

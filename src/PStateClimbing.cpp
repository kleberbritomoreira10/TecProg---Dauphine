#include "PStateClimbing.h"
#include "Logger.h"

void PStateClimbing::enter(){
	Log(DEBUG) << "STATE CLIMBING";
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(10, 5, 1, false, 0);
}

void PStateClimbing::exit(){

}

void PStateClimbing::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	if(keyStates_[GameKeys::UP]){
		this->player->moveVertical(true, false);
	}
	if(keyStates_[GameKeys::DOWN]){
		this->player->moveVertical(false, true);
	}

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		this->player->vx = -500;
		this->player->changeState(Player::PStates::AERIAL);
		this->player->isGrounded = false;
		return;
	}

}

PStateClimbing::PStateClimbing(Player* const player_) :
	StatePlayer(player_)
{

}

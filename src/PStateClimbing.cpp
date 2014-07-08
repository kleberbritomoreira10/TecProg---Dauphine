#include "PStateClimbing.h"
#include "Logger.h"

void PStateClimbing::enter(){
	// Log(DEBUG) << "STATE CLIMBING";

	this->player->isClimbing = true;
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

    this->player->vy -= 10;
    if(!this->player->isRight){
		this->player->vx = -0.001;
    }
	else{
		this->player->vx = 0.0;
	}

	this->player->getAnimation()->changeAnimation(0, 6, 1, false, 0);

}

void PStateClimbing::exit(){
	this->player->isClimbing = false;
}

void PStateClimbing::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	this->player->moveVertical(keyStates_[GameKeys::UP], keyStates_[GameKeys::DOWN]);

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		
		this->player->vy = -700;

		if(this->player->isRight){
			this->player->vx = -500;
		}
		else{
			this->player->vx = 500;
		}

		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

	if(!this->player->isClimbing){
		this->player->vy = -1000;
		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

}

PStateClimbing::PStateClimbing(Player* const player_) :
	StatePlayer(player_)
{

}

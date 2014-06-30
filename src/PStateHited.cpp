#include "PStateHited.h"
#include "Logger.h"

void PStateHited::enter(){
	Log(DEBUG) << "STATE ATTACK JUMPING";
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(4, 8, 1, false, 0);

	int direction = 1;
	if(this->player->isRight){
		direction = -1;
	}
	// this->player->vx = 1000 * direction;
}

void PStateHited::exit(){

}

void PStateHited::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	

}

PStateHited::PStateHited(Player* const player_) :
	StatePlayer(player_)
{

}

#include "PStateAttackJumping.h"
#include "Logger.h"

void PStateAttackJumping::enter(){
	Log(DEBUG) << "STATE ATTACK JUMPING";
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 97;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(0, 4, 5, false, 0.5);
	

}

void PStateAttackJumping::exit(){

}

void PStateAttackJumping::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	

}

PStateAttackJumping::PStateAttackJumping(Player* const player_) :
	StatePlayer(player_)
{

}

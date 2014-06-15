#include "PStateAttackJumping.h"
#include "Logger.h"

void PStateAttackJumping::enter(){
	Log(DEBUG) << "STATE ATTACK JUMPING";
	
   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 97;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(5, 9, 3, false, 0.3);
}

void PStateAttackJumping::exit(){

}

void PStateAttackJumping::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
	
	if(this->player->getAnimation()->getCurrentFrame() == 3){
		this->player->changeState(Player::PStates::AERIAL);
	}
}

PStateAttackJumping::PStateAttackJumping(Player* const player_) :
	StatePlayer(player_)
{

}

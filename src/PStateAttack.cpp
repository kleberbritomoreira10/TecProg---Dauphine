#include "PStateAttack.h"
#include "Logger.h"

void PStateAttack::enter(){
	this->box.x = (int)this->player->getWidth() / 4 - 33;
	this->box.y = (int)this->player->getHeight() / 3.5;
	this->box.w = (int)this->player->getWidth() / 1.7;
	this->box.h = (int)this->player->getHeight() / 3.5;

	this->player->getAnimation()->changeAnimation(4, 14, 13, false, 0.466);
}

void PStateAttack::exit(){

}

void PStateAttack::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	if(this->player->getAnimation()->getCurrentFrame() == 13){
		this->player->changeState(Player::PStates::IDLE);
	}
}

PStateAttack::PStateAttack(Player* const player_) :
	StatePlayer(player_)
{

}

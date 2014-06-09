#include "PStateSetUpTrap.h"
#include "Logger.h"

void PStateSetUpTrap::enter(){
	this->box.x = (int)this->player->getWidth() / 4 - 33;
    this->box.w = (int)this->player->getWidth() / 1.7;
	this->box.y = (int)this->player->getHeight() / 2;
	this->box.h = (int)this->player->getHeight() / 2;

	this->player->getAnimation()->changeAnimation(10, 12, 11, false, 1.1);
	this->player->isGrounded = true;
}

void PStateSetUpTrap::exit(){

}

void PStateSetUpTrap::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	if(this->player->getAnimation()->getCurrentFrame() == 11){
		this->player->useTrap();
		this->player->changeState(Player::PStates::IDLE);
	}
}

PStateSetUpTrap::PStateSetUpTrap(Player* const player_) :
	StatePlayer(player_)
{

}

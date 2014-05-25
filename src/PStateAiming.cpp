#include "PStateAiming.h"
#include "Logger.h"
#define RIGHTD 1
#define LEFTD -1
#define NONED 0

void PStateAiming::enter(){

	if(this->player->isRight){
		this->player->getCrosshair()->x = this->player->x + this->player->getWidth();
	}
	else{
		this->player->getCrosshair()->x = this->player->x - this->player->getCrosshair()->getWidth();
	}

	this->player->getCrosshair()->y = this->player->y + this->player->getHeight() - this->player->getCrosshair()->getHeight();
}

void PStateAiming::exit(){
}

void PStateAiming::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	if(!keyStates_[GameKeys::DOWN]){
		this->player->getCrosshair()->y = -600;
		this->player->getCrosshair()->x = -600;
		this->player->changeState(Player::PStates::IDLE);
		return;
	}

	if(keyStates_[GameKeys::SPACE]){
		this->player->useBombPotion(this->player->getBombPotion(), 15, this->absoluteCrosshairPlayerDistance());
	}
	
	if(keyStates_[GameKeys::LEFT]){
		
		if(this->player->isRight){
			if((this->player->getCrosshair()->x > (this->player->x + this->player->getWidth()))){
				this->player->aim(this->player->getCrosshair(), LEFTD);
			}
				
		}
		
		else if (this->absoluteCrosshairPlayerDistance() < 300) {
			this->player->aim(this->player->getCrosshair(), LEFTD);
		}
		return;
	}

	else if(keyStates_[GameKeys::RIGHT]){
		if(!this->player->isRight){
			if((this->player->getCrosshair()->x < (this->player->x - this->player->getCrosshair()->getWidth()))){
				this->player->aim(this->player->getCrosshair(), RIGHTD);
			}	
		}
		else if (this->absoluteCrosshairPlayerDistance() < 300) {
			this->player->aim(this->player->getCrosshair(), RIGHTD);
		}
		return;
	}

	else{
		this->player->aim(this->player->getCrosshair(), NONED);
		return;
	}


}

PStateAiming::PStateAiming(Player* const player_) :
	StatePlayer(player_)
{

}

int PStateAiming::absoluteCrosshairPlayerDistance(){
	return (int)(this->player->isRight ? (this->player->getCrosshair()->x - this->player->x - this->player->getWidth()) : (this->player->x - this->player->getCrosshair()->x) - this->player->getCrosshair()->getWidth());
}

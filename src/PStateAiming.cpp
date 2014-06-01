#include "PStateAiming.h"
#include "Logger.h"
#include "Game.h"
#define RIGHTD 1
#define LEFTD -1
#define NONED 0

#define THROW_STRENGTH 30

#define MAX_DISTANCE 300
#define MIN_DISTANCE 50

void PStateAiming::enter(){

	if(this->player->isRight){
		this->player->getCrosshair()->x = this->player->x + this->player->getWidth();
	}
	else{
		this->player->getCrosshair()->x = this->player->x - this->player->getCrosshair()->getWidth();
	}

	this->player->getCrosshair()->y = this->player->y + this->player->getHeight() - this->player->getCrosshair()->getHeight();

	if(this->player->potions.size() < 3){

		Sprite* spritePotion = Game::instance().getResources().get("res/images/potion.png");
		
		if(spritePotion != nullptr){
			Potion* potion = new Potion(300,300,spritePotion,this->player);	
			if(potion != nullptr){
				Log(DEBUG) << potion->x;
				this->player->potions.push_back(potion);
			}
		}
	}
}

void PStateAiming::exit(){
}

void PStateAiming::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	if(!keyStates_[GameKeys::AIM]){
		this->player->getCrosshair()->y = -600;
		this->player->getCrosshair()->x = -600;
		this->player->changeState(Player::PStates::IDLE);
		return;
	}

	if(keyStates_[GameKeys::ACTION]){
		if(this->player->potionsLeft > 0){	
			this->player->usePotion(3 - this->player->potionsLeft, THROW_STRENGTH, this->absoluteCrosshairPlayerDistance());
			this->player->potionsLeft--;
			return;
		}
	}
	
	if(keyStates_[GameKeys::LEFT]){
		
		if(this->player->isRight){
			if((this->player->getCrosshair()->x > (this->player->x + this->player->getWidth()))){
				this->player->aim(this->player->getCrosshair(), LEFTD);
			}
				
		}
		
		else if (this->absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {
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
		else if (this->absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {
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
	int distance =  (int)(this->player->isRight ? (this->player->getCrosshair()->x - this->player->x - this->player->getWidth()) : (this->player->x - this->player->getCrosshair()->x) - this->player->getCrosshair()->getWidth());

	if(distance < MIN_DISTANCE)
		distance = MIN_DISTANCE;

	return distance;
}

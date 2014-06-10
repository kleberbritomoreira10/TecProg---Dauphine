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
	this->box.x = (int)this->player->getWidth() / 4 - 33;
	this->box.y = (int)this->player->getHeight() / 3.5;
	this->box.w = (int)this->player->getWidth() / 1.7;
	this->box.h = (int)this->player->getHeight() / 3.5;

	this->player->crosshair->activated = true;

	if(this->player->isRight){
		this->player->crosshair->x = this->player->getBoundingBox().x + this->player->getBoundingBox().w;
	}
	else{
		this->player->crosshair->x = this->player->getBoundingBox().x - this->player->crosshair->getWidth();
	}

	this->player->crosshair->y = this->player->y + this->player->getHeight() - this->player->crosshair->getHeight();

}

void PStateAiming::exit(){
	this->player->crosshair->activated = false;
}

void PStateAiming::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	this->player->crosshair->render(0.0, 0.0);

	if(!keyStates_[GameKeys::AIM]){
		this->player->changeState(Player::PStates::IDLE);
		return;
	}

	if(keyStates_[GameKeys::ACTION]){
		if(this->player->currentItem == Player::PItems::POTION){
			this->player->usePotion(THROW_STRENGTH, absoluteCrosshairPlayerDistance());
			return;
		}
	}
	
	if(keyStates_[GameKeys::LEFT]){
		
		if(this->player->isRight){
			if((this->player->crosshair->x > (this->player->getBoundingBox().x + this->player->getBoundingBox().w))){
				this->player->aim(this->player->crosshair, LEFTD);
			}
				
		}
		
		else if (absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {
			this->player->aim(this->player->crosshair, LEFTD);
		}

		return;
	}

	else if(keyStates_[GameKeys::RIGHT]){
		if(!this->player->isRight){
			if((this->player->crosshair->x < (this->player->getBoundingBox().x - this->player->crosshair->getWidth()))){
				this->player->aim(this->player->crosshair, RIGHTD);
			}	
		}
		else if (absoluteCrosshairPlayerDistance() < MAX_DISTANCE) {
			this->player->aim(this->player->crosshair, RIGHTD);
		}
		return;
	}

	else{
		this->player->aim(this->player->crosshair, NONED);
		return;
	}


}

PStateAiming::PStateAiming(Player* const player_) :
	StatePlayer(player_)
{

}

int PStateAiming::absoluteCrosshairPlayerDistance(){
	int distance = 0;

	if(this->player->isRight){
		distance = (int) this->player->crosshair->x - this->player->getBoundingBox().x - this->player->getBoundingBox().w;
	}
	else{
		distance = (int) this->player->getBoundingBox().x - this->player->crosshair->x - this->player->crosshair->getWidth();
	}

	if(distance < MIN_DISTANCE){
		distance = MIN_DISTANCE;
	}

	return distance;
}

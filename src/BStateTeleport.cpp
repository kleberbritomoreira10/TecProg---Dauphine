#include "BStateTeleport.h"
#include "Collision.h"
#include "Logger.h"

double tptime = 0;
double pX = 0;
double pY = 0;

void BStateTeleport::enter(){
	Log(DEBUG) << "STATE TELEPORT BOSS";
	this->boss->power = new Sprite("res/images/laser_sheet.png");
	this->boss->powerAnimation->changeWidthHeight(700,340);
	this->boss->powerAnimation->changeAnimation(0, 0, 3, false, 0.5);
}

void BStateTeleport::exit(){
	this->boss->powerIsActivated = false;
	tptime = 0.0;
}

void BStateTeleport::update(const double dt_){
	((void)dt_); // Unused.
	tptime += dt_;
	
	if(tptime < 3){
		this->boss->vx =0;
		this->boss->vy =0;
	}
	else if(tptime >= 3 && tptime <= 3.5){
		this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
		this->boss->vx = 0;
		if(this->boss->player->isRight){
			this->boss->x = this->boss->player->x - 150 - 50;
			this->boss->y = this->boss->player->y;
		}
		else{
			this->boss->x = this->boss->player->x + 150 + 50;
			this->boss->y = this->boss->player->y;
		}
		this->boss->isRight = this->boss->player->isRight;
		pX = this->boss->x;
		pY = this->boss->y;
		if(!this->boss->isRight){
			this->boss->powerFlip = SDL_FLIP_HORIZONTAL;
		}
		else{
			this->boss->powerFlip = SDL_FLIP_NONE;
		}
	}
	if(tptime >= 3.4 && tptime <= 5){
		if(this->boss->player->isRight){
			this->boss->powerX = pX;
			this->boss->powerY = pY;
		}
		else{
			this->boss->powerX = pX;
			this->boss->powerY = pY;
		}
		if(tptime >= 3.9){
			this->boss->powerAnimation->changeAnimation(2, 0, 1, false, 0);
		}
		this->boss->powerIsActivated = true;
		if(Collision::rectsCollided(this->boss->player->getBoundingBox(), this->boss->powerClip)){
			Log(DEBUG) << "player se fudeu";
		}
	}
	else if(tptime > 5){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateTeleport::BStateTeleport(Boss* const boss_) :
	StateBoss(boss_)
{

}

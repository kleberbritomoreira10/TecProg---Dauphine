#include "BStateTeleport.h"
#include "Logger.h"

double tptime = 0;

void BStateTeleport::enter(){
	Log(DEBUG) << "STATE TELEPORT BOSS";

}

void BStateTeleport::exit(){

}

void BStateTeleport::update(const double dt_){
	((void)dt_); // Unused.
	tptime += dt_;
	
	if(tptime < 3){
		this->boss->vx =0;
		this->boss->vy =0;
	}
	else if(tptime >= 3 && tptime <= 6){
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
	}
	else if(tptime > 6){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateTeleport::BStateTeleport(Boss* const boss_) :
	StateBoss(boss_)
{

}

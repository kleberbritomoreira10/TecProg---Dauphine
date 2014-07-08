#include "BStateIcePrision.h"
#include "Logger.h"

void BStateIcePrision::enter(){
	Log(DEBUG) << "STATE ICE PRISION BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
}

void BStateIcePrision::exit(){

}

void BStateIcePrision::update(const double dt_){
	((void)dt_); // Unused.

	this->boss->vx = 0;
	this->boss->vy = 0;
}

BStateIcePrision::BStateIcePrision(Boss* const boss_) :
	StateBoss(boss_)
{

}

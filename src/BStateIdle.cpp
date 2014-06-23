#include "BStateIdle.h"
#include "Logger.h"

double timeFalling = 0;

void BStateIdle::enter(){

	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
}

void BStateIdle::exit(){

}

void BStateIdle::update(const double dt_){
	timeFalling += dt_;
	if(timeFalling > 0.2){
		this->boss->vy = -350;
		timeFalling = 0;
	}

	this->boss->applyGravity();
}

BStateIdle::BStateIdle(Boss* const boss_) :
	StateBoss(boss_)
{

}

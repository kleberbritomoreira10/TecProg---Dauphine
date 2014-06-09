#include "EStateLock.h"
#include "Logger.h"

double timeLocked = 0;

void EStateLock::enter(){
	Log(DEBUG) << "ENTER LOCK";
	this->enemy->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->enemy->vx = 0;
}

void EStateLock::exit(){
}

void EStateLock::update(const double dt_){
	timeLocked += dt_;
	if(timeLocked > 2){
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	}
}

EStateLock::EStateLock(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

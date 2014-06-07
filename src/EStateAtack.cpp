#include "EStateAtack.h"
#include "Logger.h"

double atackTime;

void EStateAtack::enter(){
	Log(DEBUG) << "ENTER ATACK";
	atackTime = 0;
}

void EStateAtack::exit(){

}

void EStateAtack::update(const double dt_){
	atackTime += dt_;
	const double atackTotalTime = 0.4;

	this->enemy->vx = 0;
	if(atackTime > atackTotalTime){
		Enemy::pLife--;
		this->enemy->changeState(Enemy::EStates::ALERT);
	}
}

EStateAtack::EStateAtack(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

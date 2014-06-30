#include "BStateAttack.h"
#include "Logger.h"

void BStateAttack::enter(){
	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->sawPlayer = false;
}

void BStateAttack::exit(){

}

void BStateAttack::update(const double dt_){
	this->boss->usePotion(30, 10);
	this->boss->changeState(Boss::BStates::IDLE);
}

BStateAttack::BStateAttack(Boss* const boss_) :
	StateBoss(boss_)
{

}

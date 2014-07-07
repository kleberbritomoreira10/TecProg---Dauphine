#include "BStateAttack.h"
#include "Logger.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

void BStateAttack::enter(){
	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->sawPlayer = false;
}

void BStateAttack::exit(){

}

void BStateAttack::update(const double dt_){
	((void)dt_); // Unused.

	this->boss->randomSkill(rand()%6);
	this->boss->changeState(Boss::BStates::IDLE);
}

BStateAttack::BStateAttack(Boss* const boss_) :
	StateBoss(boss_)
{
	srand(time(nullptr));
}

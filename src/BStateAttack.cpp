#include "BStateAttack.h"
#include "Logger.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>

int attackIndex = 0;

void BStateAttack::enter(){
	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->sawPlayer = false;
	attackIndex = rand()%1;
}

void BStateAttack::exit(){
	this->boss->canWalk = false;
}

void BStateAttack::update(const double dt_){
	((void)dt_); // Unused.

	if(attackIndex == 3){
		this->boss->changeState(Boss::BStates::SHIELD);
	}
	else if(attackIndex == 1){
		this->boss->changeState(Boss::BStates::TELEPORT);
	}
	else if(attackIndex == 2){
		this->boss->changeState(Boss::BStates::ICEPRISION);
	}
	else if(attackIndex == 0){
		this->boss->changeState(Boss::BStates::ICEPRISION);
	}
	else{

	}

}

BStateAttack::BStateAttack(Boss* const boss_) :
	StateBoss(boss_)
{
	srand(time(nullptr));
}

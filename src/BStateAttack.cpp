#include "BStateAttack.h"
#include "Logger.h"
#include "Game.h"

void BStateAttack::enter(){
	Log(DEBUG) << "STATE ATTACK BOSS";
	this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
	this->boss->sawPlayer = false;

	Game::instance().getAudioHandler().setCurrentEffect("res/audio/FX_NADINE/FX_SUPERAAAH.wav");
	Game::instance().getAudioHandler().playEffect(0);
}

void BStateAttack::exit(){

}

void BStateAttack::update(const double dt_){
	((void)dt_); // Unused.

	this->boss->usePotion(30, 10);
	this->boss->changeState(Boss::BStates::IDLE);
}

BStateAttack::BStateAttack(Boss* const boss_) :
	StateBoss(boss_)
{

}

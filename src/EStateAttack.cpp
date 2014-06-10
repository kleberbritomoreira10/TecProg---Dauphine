#include "EStateAttack.h"
#include "Logger.h"

double attackTime; // NO

void EStateAttack::enter(){
	this->enemy->getAnimation()->changeAnimation(2, 1, 6, false, 0.6);
	attackTime = 0;
}

void EStateAttack::exit(){

}

void EStateAttack::update(const double dt_){
	attackTime += dt_;
	const double attackTotalTime = 0.6;

	/// @todo Refactor the way the enemy hurts the player.
	this->enemy->vx = 0;
	if(attackTime > attackTotalTime){
		Enemy::pLife--;
		this->enemy->changeState(Enemy::EStates::ALERT);
	}
}

EStateAttack::EStateAttack(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

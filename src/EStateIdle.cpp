#include "EStateIdle.h"
#include <cmath>
#include "SDLWrapper.h"

void EStateIdle::enter(){

}

void EStateIdle::exit(){

}

void EStateIdle::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}
	this->enemy->changeState(Enemy::EStates::PATROLLING);
	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange){
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	}
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange){
		this->enemy->changeState(Enemy::EStates::CURIOUS);
		return;
	}

}

EStateIdle::EStateIdle(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

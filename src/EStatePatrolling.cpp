#include "EStatePatrolling.h"
#include <cfloat>

void EStatePatrolling::enter(){

}

void EStatePatrolling::exit(){

}

void EStatePatrolling::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	// Patrol
	if(abs(this->enemy->x - this->enemy->originalX) < this->enemy->patrolLength){
		this->enemy->vx -= this->enemy->speed;
	}
	else{
		this->enemy->vx += this->enemy->speed;
	}

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

EStatePatrolling::EStatePatrolling(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

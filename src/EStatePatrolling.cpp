#include "EStatePatrolling.h"
#include <cfloat>
#include "Logger.h"
void EStatePatrolling::enter(){
	this->enemy->isGrounded = true;
	this->enemy->x = this->enemy->originalX;
}

void EStatePatrolling::exit(){

}

void EStatePatrolling::update(){
	// Patrol	
	if(abs(this->enemy->x - this->enemy->originalX) < this->enemy->patrolLength){
		this->enemy->vx -= this->enemy->speed;
	}
	else{
		this->enemy->vx += this->enemy->speed;
	}

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	}
	else if(abs(this->enemy->x - Enemy::px) < Enemy::curiousRange && abs(this->enemy->y - Enemy::py) < Enemy::curiousRange){
		this->enemy->changeState(Enemy::EStates::CURIOUS);
		return;
	}
	
}

EStatePatrolling::EStatePatrolling(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

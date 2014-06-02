#include "EStateCurious.h"

void EStateCurious::enter(){
	
}

void EStateCurious::exit(){

}

void EStateCurious::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}
	else{
		if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange && abs(this->enemy->y - Enemy::py) < Enemy::alertRange){
			this->enemy->changeState(Enemy::EStates::ALERT);
			return;		
		}
		else{
			this->enemy->changeState(Enemy::EStates::PATROLLING);
			return;	
		}
	}

	
}

EStateCurious::EStateCurious(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

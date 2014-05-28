#include "EStateCurious.h"
#include "Logger.h"

void EStateCurious::enter(){
	Logger::verbose("enter enemy moving");	
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
		if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange){
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

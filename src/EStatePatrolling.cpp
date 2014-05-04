#include "EStatePatrolling.h"
#include "Logger.h"

void EStatePatrolling::enter(){
	Logger::verbose("enter enemy moving");	
}

void EStatePatrolling::exit(){

}

void EStatePatrolling::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

}

EStatePatrolling::EStatePatrolling(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

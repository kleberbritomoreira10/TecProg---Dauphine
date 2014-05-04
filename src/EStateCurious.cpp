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

	
}

EStateCurious::EStateCurious(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

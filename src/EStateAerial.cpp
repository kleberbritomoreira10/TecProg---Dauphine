#include "EStateAerial.h"

void EStateAerial::enter(){

}

void EStateAerial::exit(){

}

void EStateAerial::update(){
	// Idle
    if(this->enemy->isGrounded){
    	if(this->enemy->patrol){
	    	this->enemy->changeState(Enemy::EStates::PATROLLING);
    	}
    	else{
	    	this->enemy->changeState(Enemy::EStates::IDLE);
    	}
    	return;
    }

	// Gravity
	this->enemy->applyGravity();
}

EStateAerial::EStateAerial(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

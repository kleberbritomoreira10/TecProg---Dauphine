#include "EStateCurious.h"

void EStateCurious::enter(){
	this->enemy->jump();
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

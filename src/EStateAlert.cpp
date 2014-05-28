#include "EStateAlert.h"

void EStateAlert::enter(){

}

void EStateAlert::exit(){

}

void EStateAlert::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	if(this->enemy->x - Enemy::px < 0.0){
		this->enemy->vx += 6.5;
	}
	else{
		this->enemy->vx -= 6.5;
	}
}

EStateAlert::EStateAlert(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

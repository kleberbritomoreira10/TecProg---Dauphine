#include "EStateMoving.h"
#include "Logger.h"

void EStateMoving::enter(){
	Logger::log("enter enemy moving");	
}

void EStateMoving::exit(){

}

void EStateMoving::update(){
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

EStateMoving::EStateMoving(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

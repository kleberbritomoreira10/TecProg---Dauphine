#include "EStateIdle.h"
#include "Logger.h"
#include <cmath>
#include "SDLWrapper.h"

void EStateIdle::enter(){
	Logger::log("enter enemy idle");	
}

void EStateIdle::exit(){

}

void EStateIdle::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	if(abs(this->enemy->x - Enemy::px) < 300.0){
		this->enemy->changeState(Enemy::EStates::MOVING);
		return;
	}
}

EStateIdle::EStateIdle(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

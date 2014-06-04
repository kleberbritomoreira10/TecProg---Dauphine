#include "EStateAlert.h"
#include "Logger.h"

void EStateAlert::enter(){
	Log(DEBUG) << "ENTER ALERT";
	this->enemy->speed = 6.5;
}

void EStateAlert::exit(){
}

void EStateAlert::update(const double dt_){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	if(this->enemy->x - Enemy::px < 0.0){
		this->enemy->vx += this->enemy->speed;

	}
	else{
		this->enemy->vx -= this->enemy->speed;
	}

	if(abs(this->enemy->x - Enemy::px) < 100){
		this->enemy->vx = 0;
	}

	if(!(abs(this->enemy->x - Enemy::px) < Enemy::alertRange*2 && abs(this->enemy->y - Enemy::py) < Enemy::alertRange)){
		this->enemy->changeState(Enemy::EStates::PATROLLING);
		return;
	}	
}

EStateAlert::EStateAlert(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

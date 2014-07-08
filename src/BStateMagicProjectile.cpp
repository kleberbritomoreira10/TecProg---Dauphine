#include "BStateMagicProjectile.h"
#include "Logger.h"
#include "Sprite.h"
#include "Collision.h"

double projectileTime = 0.0;
double mpX = 0;
double mpY = 0;

void BStateMagicProjectile::enter(){
	Log(DEBUG) << "STATE MAGIC PROJECTILE BOSS";
	this->boss->power = new Sprite("res/images/projectile.png");
	this->boss->powerAnimation->changeWidthHeight(50,50);
	this->boss->powerAnimation->changeAnimation(0, 0, 4, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerX = this->boss->x;
	this->boss->powerY = this->boss->y;
	this->boss->powerIsActivated = true;
	mpX = this->boss->player->x;
	mpY = this->boss->player->y;
}

void BStateMagicProjectile::exit(){
	this->boss->powerIsActivated = false;
}

void BStateMagicProjectile::update(const double dt_){
	projectileTime += dt_;
	if(this->boss->powerX < mpX){
		this->boss->powerX+=5;
	}
	else{
		this->boss->powerX-=5;
	}
	if(this->boss->powerY < mpY){
		this->boss->powerY+=5;
	}
	else{
		this->boss->powerY-=5;
	}
	if(projectileTime>3){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateMagicProjectile::BStateMagicProjectile(Boss* const boss_) :
	StateBoss(boss_)
{

}

#include "BStateMagicProjectile.h"
#include "Logger.h"
#include "Sprite.h"
#include "Collision.h"

double projectileTime = 0.0;

void BStateMagicProjectile::enter(){
	Log(DEBUG) << "STATE MAGIC PROJECTILE BOSS";
	this->boss->power = new Sprite("res/images/ice_prision.png");
	this->boss->powerAnimation->changeWidthHeight(340,1020);
	this->boss->powerAnimation->changeAnimation(0, 0, 2, false, 0.5);
}

void BStateMagicProjectile::exit(){
	this->boss->powerIsActivated = false;
}

void BStateMagicProjectile::update(const double dt_){

}

BStateMagicProjectile::BStateMagicProjectile(Boss* const boss_) :
	StateBoss(boss_)
{

}

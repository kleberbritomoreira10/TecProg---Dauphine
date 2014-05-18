#include "BombPotion.h"

BombPotion::BombPotion(const double x_, const double y_, Sprite* const sprite_) :
	Entity(x_, y_, sprite_),
	activated(false),
	isRight(true),
	strength(0),
	vy(0)
{

}

BombPotion::~BombPotion(){

}

void BombPotion::update(const double dt_){
	if(activated){
		if(isRight){
			this->x+= this->strength;
		}
		else{
			this->x-= this->strength;
		}
		this->vy += 20;
		this->y += this->vy * dt_;
	}
}
		
void BombPotion::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}


#include "BombPotion.h"
#include "Logger.h"

#include <iostream>

BombPotion::BombPotion(const double x_, const double y_, Sprite* const sprite_) :
	Entity(x_, y_, sprite_),
	activated(false),
	isRight(true),
	strength(0),
	vx(0),
	vy(0)
{

}

BombPotion::~BombPotion(){

}

void BombPotion::update(const double dt_){
	if(activated){

		if(this->vx <= this->distance){
			if(isRight){
				this->x+= this->strength;
			}
			else{
				this->x-= this->strength;
			}
				
			this->vx += this->strength;	
		}
		else{

		}					
		
		if(vx < ((int)this->distance/2))
			this->y -=  vy;
		else
			this->y +=  1.1*vy;
			
//		this->y += (this->vx * this->vx)/100 * dt_;
	}
}
		
void BombPotion::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}


#include "BombPotion.h"
#include "Logger.h"

BombPotion::BombPotion(const double x_, const double y_, Sprite* const sprite_) :
	Entity(x_, y_, sprite_),
	activated(false),
	isRight(true),
	strength(0),
	vx(0)
{

}

BombPotion::~BombPotion(){

}

void BombPotion::update(const double dt_){
	if(activated){
		if(this->vx <= this->distance - 100){
			if(isRight){
				this->x+= this->strength;
			}
			else{
				this->x-= this->strength;
			}
		}
		else{

		}
		this->vx += this->strength;
		this->y += (this->vx * this->vx)/400 * dt_;
	}
}
		
void BombPotion::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}


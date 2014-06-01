#include "Potion.h"
#include "Logger.h"
#include <cmath>

#include <iostream>

Potion::Potion(const double x_, const double y_, Sprite* const sprite_, Player* player) :
	DynamicEntity(x_, y_, sprite_),
	activated(false),
	strength(0),
	flightTime(0)
{

}

Potion::~Potion(){

}

void Potion::update(const double dt_){

	const int angle = 360 - 45;
	const double gravity = 35;

	if(activated){

		this->flightTime +=dt_;

		if(this->isRight)
			this->x += (this->distance/300.0)*(this->vx + this->strength * cos(angle/57.29) * flightTime);
		else
			this->x -= (this->distance/300.0)*(this->vx + this->strength * cos(angle/57.29) * flightTime);

		this->y -= this->vy + this->strength * sin(angle/57.29) * flightTime - 0.5*gravity*flightTime*flightTime;
	}
}

void Potion::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
}

void Potion::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

Sprite* Potion::getSprite(){
	return this->sprite;
}
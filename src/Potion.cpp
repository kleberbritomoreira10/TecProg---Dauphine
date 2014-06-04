#include "Potion.h"
#include "Logger.h"
#include <cmath>

Potion::Potion(const double x_, const double y_, const std::string& path_, const int strength_,
	const int distance_, const bool isRight_) :

	DynamicEntity(x_, y_, path_),
	activated(true),
	strength(strength_),
	distance(distance_),
	flightTime(0.0)
{
	this->isRight = isRight_;
	if(this->isRight){
		this->x -= this->width;
	}

    this->y = this->y + 100;
    this->vx = 5;    
    this->vy = 5;
}

Potion::~Potion(){

}

void Potion::update(const double dt_){

	const int angle = 360 - 45;
	const double gravity = 35;

	if(activated){

		this->flightTime +=dt_;

		const double speedXIdk = (this->distance/300.0)*(this->vx + this->strength * cos(angle/57.29) * flightTime);
		const double speedYIdk = (this->vy + this->strength * sin(angle/57.29) * flightTime - 0.5*gravity*flightTime*flightTime);

		if(this->isRight){
			this->x += speedXIdk;
		}
		else{
			this->x -= speedXIdk;
		}

		this->y -= speedYIdk;
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

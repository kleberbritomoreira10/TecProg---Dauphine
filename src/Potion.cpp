#include "Potion.h"
#include "Logger.h"
#include <cmath>

Potion::Potion(const double x_, const double y_, const std::string& path_, const int strength_, const int inertia_,
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

    Log(DEBUG) << inertia_;

    this->vx = 5 + abs(inertia_/80);    
    this->vy = 5;
}

Potion::~Potion(){

}

void Potion::update(const double dt_){

	const int angle = 360 - 45;
	const double gravity = 35;

    updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

	if(this->activated){

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
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
       if((int)this->y%64 > 0){
         	this->y += 64 -(int)this->y%64 + 1; 
         	this->strength = 0.0;
         	this->activated = false;
    	}
	}

    if(detections_.at(CollisionSide::SOLID_BOTTOM)){

    	this->strength = 0.0;
    	this->activated = false;
    }

    if(detections_.at(CollisionSide::SOLID_LEFT)){
        this->x -= (int)(this->x + this->width)%64 + 1;
        this->strength = 0.0;
        this->activated = false;
    }

    if(detections_.at(CollisionSide::SOLID_RIGHT)){
        if((int)this->x%64 > 0){
         	this->x += (64 - (int)this->x%64) + 1;
         	this->vx = 0.0;
        }
        this->activated = false;
    }
}

void Potion::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Potion::updateBoundingBox(){
	this->boundingBox.x = (int) this->x;
    this->boundingBox.y = (int) this->y;
    this->boundingBox.w = (int) this->width;
    this->boundingBox.h = (int) this->height;
}

#include "Crosshair.h"

Crosshair::Crosshair(const double x_, const double y_, Sprite* const sprite_) :
	Entity(x_, y_, sprite_),
	activated(false)
{

}

Crosshair::~Crosshair(){

}

void Crosshair::update(const double dt_){
	/*if(activated){
		if(isRight){
			this->x+= this->strength;
		}
		else{
			this->x-= this->strength;
		}
		this->vy += 20;
		this->y += this->vy * dt_;
	}*/
}
		
void Crosshair::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}
unsigned int Crosshair::getWidth(){
	if(this->sprite)
		return this->sprite->getWidth();

	return 0;
}

unsigned int Crosshair::getHeight(){
	if(this->sprite)
		return this->sprite->getHeight();

	return 0;
}


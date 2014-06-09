#include "Trap.h"
#include "Logger.h"

Trap::Trap(const double x_, const double y_, const std::string& path_):
	DynamicEntity(x_, y_, path_),
	activated(true)
{

}

Trap::~Trap(){

}

void Trap::update(const double dt_){
    
}

void Trap::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr && activated){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, nullptr, false, this->vx*3/2, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

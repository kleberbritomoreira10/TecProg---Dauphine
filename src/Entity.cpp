#include "Entity.h"
#include "SDLWrapper.h"

Entity::Entity(const double x_, const double y_, Sprite* const sprite_) :
    x(x_),
    y(y_),
    isRight(true),
    sprite(sprite_),
    width(this->sprite->getWidth()),
    height(this->sprite->getHeight()),
    clip{0,0,0,0}
{
	// Only serves as the initializer for the derived classes.
}

Entity::~Entity(){

}

unsigned int Entity::getWidth(){
	return this->width;
}

unsigned int Entity::getHeight(){
	return this->height;
}

SDL_Rect& Entity::getClip(){
	return this->clip;
}

#include "Entity.h"
#include "SDLWrapper.h"
#include "Logger.h"

Entity::Entity(const double x_, const double y_, Sprite* const sprite_) :
    x(x_),
    y(y_),
    isRight(true),
    sprite(sprite_),
    width(0),
    height(0),
    animationClip{0,0,0,0},
    boundingBox{0,0,0,0}
{
    // Only serves as the initializer for the derived classes.

    if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();
    }
    else{
        Log(WARN) << "Entity sprite is null, width and height will be undefined.";
    }
}

Entity::~Entity(){

}

unsigned int Entity::getWidth(){
	return this->width;
}

unsigned int Entity::getHeight(){
	return this->height;
}

SDL_Rect& Entity::getAnimationClip(){
	return this->animationClip;
}

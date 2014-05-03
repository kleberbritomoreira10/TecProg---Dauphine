#include "Entity.h"
#include "SDLWrapper.h"

Entity::Entity(const double x_, const double y_, Sprite* const sprite_) :
    x(x_),
    y(y_),
    sprite(sprite_),
    width(0),
    height(0),
    clip{0,0,0,0}
{
	// Only serves as the initializer for the derived classes.
	/// @todo Fix magic numbers.
	if(this->sprite != nullptr){
		this->width = 229;
		this->height = 229;
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

SDL_Rect& Entity::getClip(){
	return this->clip;
}

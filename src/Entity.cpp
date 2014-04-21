#include "Entity.h"

Entity::Entity(double x_, double y_, Sprite* sprite_) :
    x(x_),
    y(y_),
    sprite(sprite_)
{
	// Only serves as the initializer for the derived classes.
}

Entity::~Entity(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

unsigned int Entity::getWidth(){
	return this->width;
}

unsigned int Entity::getHeight(){
	return this->height;
}

#include "Entity.h"

Entity::Entity(double x_, double y_, Sprite* sprite_) :
    x(x_),
    y(y_),
    sprite(sprite_),
    width(0),
    height(0)
{
	// Only serves as the initializer for the derived classes.
	if(this->sprite != nullptr){
		this->width = this->sprite->getWidth();
		this->height = this->sprite->getHeight();
	}

}

Entity::~Entity(){
	if(this->sprite != nullptr){
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

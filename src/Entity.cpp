#include "Entity.h"

Entity::Entity(double x_, double y_, Sprite *sprite_) :
    x(x_),
    y(y_),
    sprite(sprite_)
{
	// Only serves as the initializer for the derived classes.
}

Entity::~Entity(){
	this->x = 0;
	this->y = 0;

	/// @todo: Maybe this isn't the best place to delete the Sprite object.
	this->sprite->free();
	delete this->sprite;
	this->sprite = nullptr;
}

unsigned int Entity::getWidth(){
	return this->width;
}

unsigned int Entity::getHeight(){
	return this->height;
}

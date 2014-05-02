#include "Entity.h"
#include "SDLWrapper.h"

Entity::Entity(double x_, double y_, Sprite* sprite_) :
    x(x_),
    y(y_),
    sprite(sprite_),
    clip(new SDL_Rect()),
    width(0),
    height(0)
{
	// Only serves as the initializer for the derived classes.
	if(this->sprite != nullptr){
		this->width = 229;
		this->height = 229;
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

Sprite* Entity::getSprite(){
	return this->sprite;
}

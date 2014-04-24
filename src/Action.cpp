#include "Action.h"

Action::Action() :
	sprite(nullptr),
	player(nullptr)
{
	// Only serves as the initializer for the derived classes.
}

Action::~Action(){
	if(this->player != nullptr){
		delete this->player;
		this->player = nullptr;
	}

	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

Player* Action::getPlayer(){
	return this->player;
}

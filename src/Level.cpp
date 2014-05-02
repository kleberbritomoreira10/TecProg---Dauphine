#include "Level.h"

Level::Level() :
	width(0),
	height(0),
	player(nullptr),
	camera(nullptr)
{
	// Only serves as the initializer for the derived classes.
}

Level::~Level(){
	if(this->camera != nullptr){
		delete this->camera;
		this->camera = nullptr;
	}
}

unsigned int Level::getWidth(){
	return this->width;
}

unsigned int Level::getHeight(){
	return this->height;
}

Player* Level::getPlayer(){
	return this->player;
}

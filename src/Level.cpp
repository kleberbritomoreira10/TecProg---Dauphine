#include "Level.h"
#include "Logger.h"

Level::Level() :
	background(nullptr),
	width(0),
	height(0),
	player(nullptr),
	camera(nullptr)
{
	
}

Level::~Level(){
	this->width = 0;
	this->height = 0;
	this->player = nullptr;
	this->camera = nullptr;

	/// @todo: Maybe this isn't the best place to delete the Sprite object.
	this->background->free();
	this->background = nullptr;
	delete this->background;
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

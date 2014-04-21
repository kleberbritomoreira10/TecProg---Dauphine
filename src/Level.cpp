#include "Level.h"
#include "Logger.h"

Level::Level(Sprite *background_) :
	background(background_),
	width(0),
	height(0),
	player(nullptr),
	camera(nullptr)
{
	if(this->background != nullptr){
		this->width = this->background->getWidth();
		this->height = this->background->getHeight();
	}
	else{
		Logger::warning("Level background is null! No background will be set.");
	}	
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

#include "Level.h"
#include "Logger.h"

Level::Level(Sprite *background_){
	if(background != nullptr){
		this->background = background_;
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
	this->background = nullptr;
}

void Level::update(){
	this->player->setCameraXY(this->camera->getClip().x, this->camera->getClip().y);
	this->player->setLevelWH(this->width, this->height);
	this->camera->setPlayerXY(this->player->x, this->player->y);
	this->camera->setPlayerWH(this->player->getWidth(), this->player->getHeight());
	this->camera->setLevelWH(this->width, this->height);
}

void Level::render(SDL_Rect &clip_){
	if(this->background != nullptr){
		this->background->render(0, 0, &clip_);
	}
	else{
		Logger::warning("No background set for this Level!");
	}
}

unsigned int Level::getWidth(){
	return this->width;
}

unsigned int Level::getHeight(){
	return this->height;
}

void Level::setPlayer(Player &player_){
	this->player = &player_;
}

void Level::setCamera(Camera &camera_){
	if(this->player != nullptr){
		this->camera = &camera_;

		update();
	}
	else{
		Logger::warning("Shouldn't set the camera before the player, in Level!");
	}
}

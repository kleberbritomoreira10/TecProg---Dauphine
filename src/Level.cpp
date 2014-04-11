#include "Level.h"
#include "Logger.h"

Level::Level(unsigned int width_, unsigned int height_){
	this->width = width_;
	this->height = height_;
}

Level::~Level(){
	this->width = 0;
	this->height = 0;
	this->player = nullptr;
	this->camera = nullptr;
	this->background = nullptr;
}

void Level::update(){
	this->player->setCameraXY(this->camera->clip.x, this->camera->clip.y);
	this->player->setLevelWH(this->width, this->height);
	this->camera->setPlayerXY(this->player->x, this->player->y);
	this->camera->setPlayerWH(this->player->width, this->player->height);
	this->camera->setLevelWH(this->width, this->height);
}

void Level::render(SDL_Rect *clip_){
	if(this->background != nullptr){
		this->background->render(0, 0, clip_);
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

void Level::setBackground(Sprite *background_){
	this->background = background_;
}

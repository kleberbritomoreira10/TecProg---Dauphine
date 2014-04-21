#include "LevelOne.h"
#include "Logger.h"

LevelOne::LevelOne(Sprite *background_) :
	Level(background_)
{
	load();
}

LevelOne::~LevelOne(){
	unload();
}

void LevelOne::update(double dt_){
	this->player->setCameraXY(this->camera->getClip().x, this->camera->getClip().y);
	this->camera->setPlayerXY(this->player->x, this->player->y);
	this->camera->setPlayerWH(this->player->getWidth(), this->player->getHeight());

	// Update all the entities in the list.
	for(Entity *entity : entities){
        entity->update(dt_);
	}

}

void LevelOne::render(SDL_Rect &clip_){
	if(this->background != nullptr){
		this->background->render(0, 0, &clip_);
	}
	else{
		Logger::warning("No background set for this Level!");
	}

	// Render all the entities in the list.
	for(Entity *entity : entities){
        entity->render();
	}

}

void LevelOne::load(){
	Logger::log("Loading level 1...");
}

void LevelOne::unload(){
	Logger::log("Unloading level 1...");
}

void LevelOne::setPlayer(Player &player_){
	this->player = &player_;
	this->player->setLevelWH(this->width, this->height);
	addEntity(this->player);
}

void LevelOne::setCamera(Camera &camera_){
	if(this->player != nullptr){
		this->camera = &camera_;
		this->camera->setLevelWH(this->width, this->height);
	}
	else{
		Logger::warning("Shouldn't set the camera before the player, in Level!");
	}
}

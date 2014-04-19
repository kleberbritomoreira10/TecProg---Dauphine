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

void Level::update(double dt_){
	this->player->setCameraXY(this->camera->getClip().x, this->camera->getClip().y);
	this->camera->setPlayerXY(this->player->x, this->player->y);
	this->camera->setPlayerWH(this->player->getWidth(), this->player->getHeight());

	// Update all the entities in the list.
	for(Entity *entity : entities){
        entity->update(dt_);
	}

}

void Level::render(SDL_Rect &clip_){
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

unsigned int Level::getWidth(){
	return this->width;
}

unsigned int Level::getHeight(){
	return this->height;
}

void Level::setPlayer(Player &player_){
	this->player = &player_;
	this->player->setLevelWH(this->width, this->height);
	addEntity(this->player);
}

void Level::setCamera(Camera &camera_){
	if(this->player != nullptr){
		this->camera = &camera_;
		this->camera->setLevelWH(this->width, this->height);
	}
	else{
		Logger::warning("Shouldn't set the camera before the player, in Level!");
	}
}

void Level::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

void Level::load(){
}
void Level::unload(){
}

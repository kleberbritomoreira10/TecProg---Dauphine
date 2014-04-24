#include "Tile.h"
#include "Logger.h"

Tile::Tile(double x_, double y_, Sprite* sprite_) :
	Entity(x_, y_, sprite_),
	solid(false)
{
	if(this->sprite == nullptr){
		Logger::warning("Tile sprite is null!");
	}
}

Tile::~Tile(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

void Tile::update(double dt_){

}

void Tile::render(const double cameraX_, const double cameraY_){
	if(this->sprite != nullptr){
		const double dx = this->x - cameraX_;
		const double dy = this->y - cameraY_;
		this->sprite->render(dx, dy);
	}
}

bool Tile::isSolid(){
	return this->solid;
}

#include "Tile.h"
#include "Logger.h"

Tile::Tile(const int x_, const int y_, const int tileType_) :
	type(tileType_),
	rectangle{x_, y_, TILE_WIDTH, TILE_HEIGHT}
{

}

Tile::~Tile(){

}

SDL_Rect& Tile::getRectangle(){
	return this->rectangle;
}

int Tile::getType(){
	return this->type;
}

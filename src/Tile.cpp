#include "Tile.h"
#include "Logger.h"

Tile::Tile(const int x_, const int y_, const int tileType_) :
	type(tileType_),
	rectangle{x_, y_, TILE_SIZE, TILE_SIZE}
{
	switch(this->type){
		case TileCode::WALL3:
		case TileCode::FLOOR1:
		case TileCode::FLOOR2:
			this->solid = false;
			break;
		default:
			this->solid = true;
	}
}

Tile::~Tile(){

}

SDL_Rect& Tile::getRectangle(){
	return this->rectangle;
}

int Tile::getType(){
	return this->type;
}

bool Tile::isSolid(){
	return this->solid;
}

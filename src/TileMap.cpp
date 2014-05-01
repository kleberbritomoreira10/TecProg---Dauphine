#include "TileMap.h"
#include "Configuration.h"
#include "Logger.h"

#include "Util.h"

TileMap::TileMap(const std::vector<int>& tileData_) :
	Entity(0.0, 0.0, new Sprite("res/tilesheet.png"))
{
	clipTiles();
	create(tileData_);
}

void TileMap::create(const std::vector<int>& tileData_){
	int tileX = 0;
	int tileY = 0;

	for(std::vector<int>::const_iterator it = tileData_.begin(); it != tileData_.end(); it++){

		this->tiles.push_back(new Tile(tileX, tileY, (*it)));

		tileX += TILE_SIZE;
		if(tileX >= 1920){
			tileX = 0;
			tileY += TILE_SIZE;
		}
	}
}

TileMap::~TileMap(){
	for(std::vector<Tile*>::const_iterator it = tiles.begin(); it != tiles.end(); it++){
		delete (*it);
	}
}

void TileMap::update(const double dt_){
	(void(dt_));
}

void TileMap::render(const double cameraX_, const double cameraY_){
	for(std::vector<Tile*>::const_iterator it = tiles.begin(); it != tiles.end(); it++){
		SDL_Rect camera = {(int)cameraX_, (int)cameraY_, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()};
		if(Util::checkCollision(camera, (*it)->getRectangle())){
			const int dx = (*it)->getRectangle().x - cameraX_;
			const int dy = (*it)->getRectangle().y - cameraY_;
			this->sprite->render(dx, dy, &clips[(*it)->getType()]);
		}
	}
}

void TileMap::clipTiles(){
	//Clip the sprite sheet
	int xClip = 0;
	int yClip = 0;
	for(int i = 0; i < TileCode::TOTAL; i++){

		if(i == TILE_PER_ROW_IMAGE){
			xClip = 0;
			yClip++;
		}

		clips[i].x = TILE_WIDTH * xClip;
		clips[i].y = TILE_HEIGHT * yClip;

		clips[i].w = TILE_WIDTH;
		clips[i].h = TILE_HEIGHT;

		xClip++;

	}
}

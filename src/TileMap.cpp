#include "TileMap.h"
#include "Configuration.h"
#include "Logger.h"
#include "Game.h"
#include "Collision.h"

TileMap::TileMap(const std::vector<int>& tileData_, const std::string& path_) :
	Entity(0.0, 0.0, Game::instance().getResources().get(path_))
{
	clipTiles();
	create(tileData_);
}

void TileMap::create(const std::vector<int>& tileData_){
	int tileX = 0;
	int tileY = 0;

	for(auto tileData : tileData_){
		this->tiles.push_back(new Tile(tileX, tileY, tileData));

		tileX += TILE_SIZE;
		if(tileX >= 1920){
			tileX = 0;
			tileY += TILE_SIZE;
		}
	}
}

TileMap::~TileMap(){
	for(auto tile : this->tiles){
		delete tile;
	}
}

void TileMap::update(const double dt_){
	(void(dt_));
}

void TileMap::render(const double cameraX_, const double cameraY_){
	SDL_Rect camera = {(int)cameraX_, (int)cameraY_, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()};

	for(auto tile : this->tiles){

		bool tileIsOnScreen = Collision::checkCollision(camera, tile->getRectangle());
		if(tileIsOnScreen){

			const int dx = tile->getRectangle().x - cameraX_;
			const int dy = tile->getRectangle().y - cameraY_;
			this->sprite->render(dx, dy, &clips[tile->getType()]);
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

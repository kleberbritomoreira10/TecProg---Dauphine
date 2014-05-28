#include "TileMap.h"
#include "Game.h"
#include "Collision.h"
#include "Logger.h"

#include <iostream>

TileMap::TileMap(const std::string& mapPath_) :
	map(nullptr),
	layers(0),
	mapWidth(0),
	mapHeight(0)
{
	load(mapPath_);
}

void TileMap::load(const std::string& mapPath_){
	this->map = new Tmx::Map();
	this->map->ParseFile(mapPath_);

	if(!this->map->HasError()){

		// Iterating through the tilesets to load their respective sprites.
		for (int i = 0; i < this->map->GetNumTilesets(); ++i) {
			const Tmx::Tileset* tileset = this->map->GetTileset(i);
			addTileSet("res/maps/"+tileset->GetImage()->GetSource());
		}

		// Getting the number of layers inside the map.
		this->layers = this->map->GetNumLayers();

		// Getting the map width/height by the first layer, since theoretically the
		// width/height should be the same for all layers.
		this->mapWidth = this->map->GetLayer(0)->GetWidth();
		this->mapHeight = this->map->GetLayer(0)->GetHeight();

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int k = 0;

		// Setting the size of the TileMap::tileMatrix, defaulting values to zero.
		// First dimension.
		this->tileMatrix.resize(this->mapWidth);

		// Second dimension.
		for (i = 0; i < this->tileMatrix.size(); i++){
			this->tileMatrix[i].resize(this->mapHeight);
		}

		// Third dimension.
		for (i = 0; i < this->tileMatrix.size(); i++){
			for (j = 0; j < this->tileMatrix[0].size(); j++){
				this->tileMatrix[i][j].resize(this->layers, 0);
			}
		}

		const Tmx::Layer* currentLayer;
		for (i = 0; i < this->layers; i++){
			currentLayer = this->map->GetLayer(i);

			/// @todo Don't count Collision layer here. (currentLayer->GetName())

			// Saving all the tile IDs on the TileMap::tileMatrix
			for (j = 0; j < this->mapWidth; j++){
				for (k = 0; k < this->mapHeight; k++){
					this->tileMatrix[j][k][i] = currentLayer->GetTileId(j, k);
				}
			}
		}

		Logger::verbose("TileMap::load Map loaded (width:" +
               std::to_string(mapWidth)  +
               " height:" +
               std::to_string(mapHeight) +
               " layers:" +
               std::to_string(layers) +
               ")");
	}
	else{
		Logger::error("Unable to parse map at \"" + mapPath_ + "\" with error: " + this->map->GetErrorText());
	}
}

TileMap::~TileMap(){

}

void TileMap::renderLayer(const double cameraX_, const double cameraY_, const unsigned int layer_){
	if (this->tileSets.size() <= 0){
		Logger::error("TileSet in TileMap is null!");
		return;
	}
	if (layer_ > this->tileMatrix[0][0].size()){
		Logger::error("Invalid layer number for rendering a TileMap layer.");
		return;
	}

	const int x = this->tileMatrix.size();
	const int y = this->tileMatrix[0].size();

	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			const int index = tileMatrix[i][j][layer_];

			// If its a valid tile.
			if (index > 0){
				const double posX = ((i * TILE_SIZE) - cameraX_);
				const double posY = ((j * TILE_SIZE) - cameraY_);

				const Tmx::Tileset* ts = this->map->FindTileset(index);
				int tileSetPosition = isTileSet(ts);

				std::cout << "TILESETPOSITION: " << tileSetPosition << std::endl;

				unsigned int sw = this->tileSets.at(tileSetPosition)->getWidth();
				int tpx = sw / TILE_SIZE;
				SDL_Rect tileClip = {index%tpx * TILE_SIZE, index/tpx * TILE_SIZE, TILE_SIZE, TILE_SIZE};

				this->tileSets.at(tileSetPosition)->render(posX, posY, &tileClip);
			}
		}
	}
}

unsigned int TileMap::getMapWidth(){
	return this->mapWidth * TILE_SIZE;
}

unsigned int TileMap::getMapHeight(){
	return this->mapHeight * TILE_SIZE;
}

unsigned int TileMap::getLayers(){
	return this->layers;
}

void TileMap::addTileSet(const std::string& path_){
	Logger::verbose("Adding TileSet: " + path_);
	Sprite* newTileSet = Game::instance().getResources().get(path_);
	this->tileSets.push_back(newTileSet);
}

int TileMap::isTileSet(const Tmx::Tileset* tmxTileSet_){
	const std::string tmxPath = "res/maps/"+tmxTileSet_->GetImage()->GetSource();
	for(int i = 0; i < this->tileSets.size(); i++){
		const std::string spritePath = this->tileSets.at(i)->getPath();
		if(tmxPath == spritePath){
			return i;
		}
	}

	return -1;
}

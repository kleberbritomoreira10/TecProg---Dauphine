#include "TmxWrapper.h"

TmxWrapper::TmxWrapper(const std::string& path_) :
	map(new Tmx::Map())
{
	setFile(path_);
}

TmxWrapper::~TmxWrapper(){
	if(this->map != nullptr){
		delete this->map;
		this->map = nullptr;
	}
}

void TmxWrapper::setFile(const std::string& path_){
	this->map->ParseFile(path_);
}

std::vector<int> TmxWrapper::getTileData(){
	std::vector<int> tileData;

	// Iterate through the layers.
	for (int i = 0; i < map->GetNumLayers(); i++) {
	
		// Get a layer.
		const Tmx::Layer* layer = map->GetLayer(i);

		// Can check if a tile is flipped, remember.

		for (int y = 0; y < layer->GetHeight(); y++) {
			for (int x = 0; x < layer->GetWidth(); x++) {
				// Get the tile's id.
				const int tileId = layer->GetTileId(x, y);
				tileData.push_back(tileId);
			}
		}

	
	}
	return tileData;
}

int TmxWrapper::getMapWidth(){
	return this->map->GetWidth() * 64;
}

int TmxWrapper::getMapHeight(){
	return this->map->GetHeight() * 64;
}
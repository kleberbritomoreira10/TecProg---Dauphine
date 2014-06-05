#include "HUD.h"
#include "Game.h"
#include "Logger.h"

HUD::HUD(const double x_, const double y_, const std::string path_, int numberOfSprites_):
	Entity(x_, y_, path_),
	numberOfSprites(numberOfSprites_)
{
	
}

HUD::~HUD(){

}

void HUD::update(const double dt_){

}

void HUD::render(const double cameraX_, const double cameraY_){
	int i;
	for(i = 0; i < this->numberOfSprites; i++){
		this->hudSprites[i]->render(this->x, this->y, nullptr, false, 0.0, nullptr);
	}
}

void HUD::setSprites(const std::string path_[]){
	Log(DEBUG) << this->numberOfSprites;
	int i;
	for(i = 0; i < this->numberOfSprites; i++)
		this->hudSprites[i] = Game::instance().getResources().get(path_[i]);
}
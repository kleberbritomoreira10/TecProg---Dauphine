#include "StateGame.h"
#include "Logger.h"

StateGame::~StateGame(){
	//Logger::log("--- StateGame destructor");
	cleanEntities(); // Should be called in each state unload.
}

void StateGame::addEntity(Entity *entity){
	this->entities.push_back(entity);
}


void StateGame::cleanEntities(){
	for(auto entity : this->entities){
		delete entity;
	}

	this->entities.clear();
}

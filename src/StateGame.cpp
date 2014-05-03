#include "StateGame.h"
#include "Logger.h"

StateGame::~StateGame(){
	cleanEntities(); // Should be called in each state unload.
}

void StateGame::addEntity(Entity* const entity){
	this->entities.push_back(entity);
}


void StateGame::cleanEntities(){
	for(auto entity : this->entities){
		delete entity;
	}

	this->entities.clear();
}

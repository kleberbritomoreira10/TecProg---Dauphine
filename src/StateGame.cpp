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
	for(std::vector<Entity*>::const_iterator it = this->entities.begin(); it != this->entities.end(); it++){
		delete (*it);
	}
	this->entities.clear();
}

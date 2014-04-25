#include "GameState.h"

GameState::~GameState(){
	cleanEntities();
}

void GameState::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

void GameState::cleanEntities(){
	if(!this->entities.empty()){
		for(list<Entity *>::iterator it = this->entities.begin(); it != this->entities.end();
			it++){

			if((*it) != nullptr){
				delete (*it);
			}
		}
		entities.clear();
	}
}

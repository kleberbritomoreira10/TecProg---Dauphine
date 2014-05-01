#include "StateGame.h"

StateGame::~StateGame(){
	cleanEntities();
}

void StateGame::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

void StateGame::cleanEntities(){
	if(!this->entities.empty()){
		for(std::list<Entity *>::iterator it = this->entities.begin(); it != this->entities.end();
			it++){

			if((*it) != nullptr){
				delete (*it);
			}
		}
		entities.clear();
	}
}

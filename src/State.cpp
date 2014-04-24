#include "State.h"

State::~State(){
	cleanEntities();
}

void State::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

void State::cleanEntities(){
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

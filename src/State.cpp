#include "State.h"

State::~State(){

}

void State::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

Player* State::getPlayer(){
	return nullptr;
}

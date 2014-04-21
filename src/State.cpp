#include "State.h"

State::~State(){

}

void State::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

#include "State.h"

State::~State(){
	/// @todo Destroy entities inside list?
}

void State::addEntity(Entity *entity){
	this->entities.push_back(entity);
}

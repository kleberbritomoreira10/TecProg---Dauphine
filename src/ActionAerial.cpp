#include "ActionAerial.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionAerial::ActionAerial() :
	Action()
{

}

ActionAerial::~ActionAerial(){

}

void ActionAerial::update(double dt_){
	InputHandler* inputHandler = InputHandler::getInstance();
	const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

	// Idle
    if(this->player->isGrounded){
    	this->player->setAction((*Player::actionIdle));
    	return;
    }

	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates[GameKeys::LEFT], keyStates[GameKeys::RIGHT]);

    
}

void ActionAerial::load(){
	Logger::verbose("load-> AERIAL");
}

void ActionAerial::unload(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}

	this->player = nullptr;
}

void ActionAerial::render(){

}

void ActionAerial::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
	
}

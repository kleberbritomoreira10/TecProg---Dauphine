#include "ActionIdle.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionIdle::ActionIdle() :
	Action()
{

}

ActionIdle::~ActionIdle(){

}

void ActionIdle::update(double dt_){
	InputHandler* inputHandler = InputHandler::getInstance();
	const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

	// Aerial
	if(!this->player->isGrounded){
		this->player->setAction((*Player::actionAerial));
		return;
	}

    this->player->slowVx();

	// Jump
	if(keyStates[GameKeys::UP] && this->player->isGrounded){
		this->player->jump();
		this->player->setAction((*Player::actionAerial));
		return;
	}

	// Move
	if(keyStates[GameKeys::LEFT] || keyStates[GameKeys::RIGHT]){
		this->player->setAction((*Player::actionMoving));
		return;
	}

	if(keyStates[GameKeys::ROLL]){
        this->player->setAction((*Player::actionRolling));
        return;
    }
}

void ActionIdle::load(){
	Logger::verbose("load-> IDLE");
}

void ActionIdle::unload(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

void ActionIdle::render(){

}

void ActionIdle::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
	
}

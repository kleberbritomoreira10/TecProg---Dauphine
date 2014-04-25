#include "ActionMoving.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionMoving::ActionMoving() :
	Action()
{

}

ActionMoving::~ActionMoving(){

}

void ActionMoving::update(double dt_){
	InputHandler* inputHandler = InputHandler::getInstance();
    const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    // Aerial
    if(!this->player->isGrounded){
        this->player->setAction((*Player::actionAerial));
        return;     
    }

    // Jump
    if(keyStates[GameKeys::UP] && this->player->isGrounded){
        this->player->jump();
        this->player->setAction((*Player::actionAerial));
        return;
    }

    this->player->move(keyStates[GameKeys::LEFT], keyStates[GameKeys::RIGHT]);

    if(keyStates[GameKeys::ROLL]){
        this->player->setAction((*Player::actionRolling));
        return;
    }

    // Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->setAction((*Player::actionIdle));
        return;
    }
    
}

void ActionMoving::load(){
    Logger::verbose("load-> MOVING");
}

void ActionMoving::unload(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

void ActionMoving::render(){

}

void ActionMoving::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
}

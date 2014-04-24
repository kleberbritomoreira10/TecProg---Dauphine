#include "ActionRolling.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionRolling::ActionRolling() :
	Action()
{

}

ActionRolling::~ActionRolling(){

}

void ActionRolling::update(double dt_){
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

	// Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->setAction((*Player::actionIdle));
        return;
    }
}

void ActionRolling::load(){
	Logger::verbose("load-> ROLL");
	this->player->vx = 70 * this->player->speed;
}

void ActionRolling::unload(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

void ActionRolling::render(){

}

void ActionRolling::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
	
}

Player* ActionRolling::getPlayer(){
	return this->player;
}

#include "ActionWalking.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionWalking::ActionWalking() :
	Action()
{

}

ActionWalking::~ActionWalking(){

}

void ActionWalking::update(double dt_){
	InputHandler* inputHandler = InputHandler::getInstance();
    const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    /*if(keyStates[GameKeys::UP]){
        this->player->setAction((*Player::actionAerial));
    }
    if(keyStates[GameKeys::LEFT] || keyStates[GameKeys::RIGHT]){
    	//this->player->setState((*Player::actionRunning));
    	if(keyStates[GameKeys::LEFT]){
	        if(this->player->vx > -this->player->maxSpeed){
	            this->player->vx -= this->player->speed;
	        } 
	    }
	    else if(keyStates[GameKeys::RIGHT]){
	        if(this->player->vx < this->player->maxSpeed){
	            this->player->vx += this->player->speed;
	        }
	    }
    }
    else{
        this->player->vx *= 0.95;
    }*/
}

void ActionWalking::load(){

	Logger::verbose("Player action = WALKING");
	LuaScript luaSplash("lua/Standing.lua");
	const string standingPath = luaSplash.unlua_get<string>("standing.spritePath");

	Sprite* lStand = new Sprite(standingPath);
	this->sprite = lStand;
}

void ActionWalking::unload(){
	Logger::verbose("Player action = NOT WALKING");
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}

	this->player = nullptr;
}

void ActionWalking::render(){

}

void ActionWalking::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
	
}

#include "ActionStanding.h"
#include "LuaScript.h"
#include "InputHandler.h"
#include "Logger.h"

#include <string>
using std::string;

ActionStanding::ActionStanding() :
	Action()
{

}

ActionStanding::~ActionStanding(){

}

void ActionStanding::update(double dt_){
	InputHandler* inputHandler = InputHandler::getInstance();
    const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    if(keyStates[GameKeys::UP]){
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
    }
}

void ActionStanding::load(){
	LuaScript luaSplash("lua/Standing.lua");
	const string standingPath = luaSplash.unlua_get<string>("standing.spritePath");

	Sprite* lStand = new Sprite(standingPath);
	this->sprite = lStand;
}

void ActionStanding::unload(){
	if(this->sprite != nullptr){
		this->sprite->free();
		delete this->sprite;
		this->sprite = nullptr;
	}
}

void ActionStanding::render(){

}

void ActionStanding::setPlayer(Player* player_){
	this->player = player_;

	if(this->player == nullptr){
		Logger::warning("Setting a null player!");
	}
	
}

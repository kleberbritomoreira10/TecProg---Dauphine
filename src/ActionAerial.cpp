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

	this->player->vy += 2*this->player->speed;

	if(keyStates[GameKeys::LEFT] || keyStates[GameKeys::RIGHT]){
    	//this->player->setState((*Player::Walking));
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

void ActionAerial::load(){
	LuaScript luaSplash("lua/Standing.lua");
	const string standingPath = luaSplash.unlua_get<string>("standing.spritePath");

	Sprite* lStand = new Sprite(standingPath);
	this->sprite = lStand;

	this->player->vy = (-40) * this->player->speed;
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

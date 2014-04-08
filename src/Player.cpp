#include "Player.h"
#include "Logger.h"
#include "Configuration.h"

Player::Player(double x_, double y_, Sprite *sprite_){
	this->x = x_;
	this->y = y_;
    this->vx = 0;
    this->vy = 0;
    this->speed = 10;
    this->canMove = false;

	this->sprite = sprite_;

	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the player! Null sprite.");
	}
}

Player::~Player(){
    this->vx = 0;
    this->vy = 0;
    this->speed = 0;	
}

void Player::update(double dt_){
    this->x += this->vx * dt_;
    this->y += this->vy * dt_;
}

void Player::render(){
	this->sprite->render(this->x, this->y);
}

void Player::updateInput(bool keyState_[GK_MAX]){
    // Jump.
    if(keyState_[GK_UP]){
        this->vy -= this->speed;
    }
    else{
        if(this->y >= (Configuration::screenHeight - 100)){
            this->y = Configuration::screenHeight - 99;
            this->vy = 0;
        }
        else{
            this->vy += this->speed;
        }
    }
}

void Player::setCanMove(bool move){
	this->canMove = move;
}
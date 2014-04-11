#include "Player.h"
#include "Logger.h"
#include "Configuration.h"

Player::Player(double x_, double y_, Sprite *sprite_){
	this->x = x_;
	this->y = y_;
    this->vx = 0;
    this->vy = 0;
    this->speed = 15;
    this->maxSpeed = 0;
    this->cameraX = 0;
    this->cameraY = 0;

	this->sprite = sprite_;

	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the player! Null sprite.");
	}
}

Player::~Player(){
    this->x = 0;
    this->y = 0;
    this->vx = 0;
    this->vy = 0;
    this->speed = 0;
    this->cameraX = 0;
    this->cameraY = 0;
    this->maxSpeed = 0;
}

void Player::update(double dt_){
    /// @todo Get actual player W/H and level W/H.
    this->x += this->vx * dt_;
    if((this->x < 0) || (this->x + 100 > 3000)){
        this->x -= this->vx * dt_;
    }

    this->y += this->vy * dt_;
    if((this->y < 0) || (this->y + 100 > 540)){
        this->y -= this->vy * dt_;
    }
}

void Player::render(){
	this->sprite->render(this->x - this->cameraX, this->y - this->cameraY);
}

void Player::updateInput(bool keyState_[GK_MAX]){
    /// @todo Fix all these magic/weird numbers.

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

    if(keyState_[GK_LEFT]){
        if(this->vx > -MAX_VEL){
            this->vx -= this->speed;
        } 
    }
    else if(keyState_[GK_RIGHT]){
        if(this->vx < MAX_VEL){
            this->vx += this->speed;
        }
    }
    else{
        this->vx *= 0.95;
    }
    
}

void Player::setCameraXY(double x_, double y_){
    this->cameraX = x_;
    this->cameraY = y_;
}

#include "Player.h"
#include "Logger.h"

const int SCREEN_WIDTH = 192 * 5;
const int SCREEN_HEIGHT = 108 * 5;

Player::Player(double x_, double y_, Sprite *sprite_){
	this->x = x_;
	this->y = y_;
    this->vx = 0;
    this->vy = 0;
    this->speed = 10;

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

	/// @todo: Maybe this isn't the best place to delete the Sprite object.
	delete this->sprite;
	this->sprite = nullptr;
}

void Player::update(double dt_){
    this->x += this->vx * dt_;
    this->y += this->vy * dt_;
}

void Player::render(){
	this->sprite->render(this->x, this->y, nullptr);
}

void Player::updateInput(bool keyState_[GK_MAX]){
    // Jump.
    if(keyState_[GK_UP]){
        this->vy -= this->speed;
    }
    else{
        if(this->y >= (SCREEN_HEIGHT - 100)){
            this->y = SCREEN_HEIGHT - 99;
            this->vy = 0;
        }
        else{
            this->vy += this->speed;
        }
    }

    // Movement.
    if(keyState_[GK_LEFT]){
        this->vx -= this->speed;
    }
    else if(keyState_[GK_RIGHT]){
        this->vx += this->speed;
    }
    else{
        this->vx *= 0.98;
    }
}

#include "Player.h"
#include "Logger.h"
#include "Configuration.h"

Player::Player(double x_, double y_, Sprite *sprite_){
	this->x = x_;
	this->y = y_;
    this->vx = 0;
    this->vy = 0;
    this->speed = 15;
    this->maxSpeed = 1000;
    this->cameraX = 0;
    this->cameraY = 0;
    this->levelW = 0;
    this->levelH = 0;

	this->sprite = sprite_;

	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the player! Null sprite.");
        this->width = 0;
        this->height = 0;
	}
    else{
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();
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
    const double vxdt = this->vx * dt_;
    const double vydt = this->vy * dt_;

    this->x += vxdt;
    if(this->x < 0){
        this->x = 0;
        this->vx = 0;
    }
    else if(this->x + this->width > this->levelW){
        this->x = this->levelW - this->width;
        this->vx = 0;
    }

    this->y += vydt;
    if(this->y < 0){
        this->y = 0;
        this->vy = 0;
    }
    else if(this->y + this->height > this->levelH){
        this->y = this->levelH - this->height;
        this->vy = 0;
    }
}

void Player::render(){
    const int dx = this->x - this->cameraX;
    const int dy = this->y - this->cameraY;
	this->sprite->render(dx, dy);
}

void Player::updateInput(bool keyState_[GK_MAX]){
    /// @todo Fix all these magic/weird numbers.

    // Jump.
    if(keyState_[GK_UP]){
        this->vy -= this->speed;
    }
    else{
        this->vy += this->speed; //gravity
    }

    // Movement.
    if(keyState_[GK_LEFT]){
        if(this->vx > -this->maxSpeed){
            this->vx -= this->speed;
        } 
    }
    else if(keyState_[GK_RIGHT]){
        if(this->vx < this->maxSpeed){
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

void Player::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

#include "Player.h"
#include "Logger.h"
#include "Configuration.h"

Player::Player(double x_, double y_, Sprite *sprite_) :
    Entity(x_, y_, sprite_),
    vx(0),
    vy(0),
    speed(15),
    maxSpeed(1000),
    cameraX(0),
    cameraY(0),
    levelW(0),
    levelH(0)
{
	if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();
	}
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    this->vx = 0;
    this->vy = 0;
    this->speed = 0;
    this->cameraX = 0;
    this->cameraY = 0;
    this->maxSpeed = 0;
}

void Player::update(double dt_){
    this->x += this->vx * dt_;

    // Left wall.
    if(this->x < 0){
        this->x = 0;
        this->vx = 0;
    }
    // Right wall.
    else if(this->x + this->width > this->levelW){
        this->x = this->levelW - this->width;
        this->vx = 0;
    }

    this->y += this->vy * dt_;

    // Top wall.
    if(this->y < 0){
        this->y = 0;
        this->vy = 0;
    }
    // Bottom wall.
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

void Player::updateInput(array<bool, GameKeys::MAX> keyStates_){
    /// @todo Fix all these magic/weird numbers.

    // Jump.
    if(keyStates_[GameKeys::UP]){
        this->vy -= this->speed;
    }
    else{
        this->vy += this->speed; //gravity
    }

    // Movement.
    if(keyStates_[GameKeys::LEFT]){
        if(this->vx > -this->maxSpeed){
            this->vx -= this->speed;
        } 
    }
    else if(keyStates_[GameKeys::RIGHT]){
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

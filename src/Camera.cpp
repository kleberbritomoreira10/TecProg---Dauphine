#include "Camera.h"
#include "Logger.h"
#include "Configuration.h"

Camera::Camera(double x_, double y_, Sprite *sprite_){
	this->x = x_;
	this->y = y_;
    this->vx = 0;
    this->vy = 0;
    this->speed = 10;

    this->canMove = true;
    this->canMovePlayer = false;

	this->sprite = sprite_;
	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the camera! Null sprite.");
	}

	this->clip = {(int)x_, (int)y_, (int)Configuration::screenWidth, (int)Configuration::screenHeight};
}

Camera::~Camera(){
    this->vx = 0;
    this->vy = 0;
    this->speed = 0;	
}

void Camera::update(double dt_){
    if(this->x > Configuration::resolutionLeftLimit){
        this->vx = Configuration::resolutionLeftLimit;
        this->x = Configuration::resolutionLeftLimit -1;
        Configuration::leftLimit = 0;
        Configuration::rightLimit = 451;
    }
    else if(this->x < Configuration::resolutionRightLimit){
        this->x = Configuration::resolutionRightLimit + 1;
        this->vx = 0;
        Configuration::leftLimit = 449;
        Configuration::rightLimit = 940;
    }
    this->x += this->vx * dt_;
    this->y += this->vy * dt_;
}

void Camera::render(){
	this->sprite->render(this->x, this->y);
}

void Camera::updateInput(bool keyState_[GK_MAX]){
    // Movement.
    if(keyState_[GK_LEFT]){
        this->vx += this->speed; 
    }
    else if(keyState_[GK_RIGHT]){
        this->vx -= this->speed;
    }
    else{
        this->vx *= 0.95;
    }
}

bool Camera::getCanMove(){
    return this->canMovePlayer;
}
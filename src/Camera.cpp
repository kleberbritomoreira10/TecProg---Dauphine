#include "Camera.h"
#include "Logger.h"
#include "Configuration.h"
#include "Level.h"

Camera::Camera(){
    /// @todo If the player changes the resolution, so should this clip.
    this->playerX = 0;
    this->playerY = 0;
    this->levelW = 0;
    this->levelH = 0;
    this->clip = {0, 0, (int)Configuration::screenWidth, (int)Configuration::screenHeight};
}

Camera::~Camera(){
    this->playerX = 0;
    this->playerY = 0;
    this->levelW = 0;
    this->levelH = 0;
    this->clip = {0, 0, 0, 0};
}

void Camera::update(){
    this->clip.x = ( this->playerX + this->playerW / 2 ) - this->clip.w / 2;
    this->clip.y = ( this->playerY + this->playerH / 2 ) - this->clip.h / 2;

    if(this->clip.x < 0){
        this->clip.x = 0;
    }
    if(this->clip.y < 0){
        this->clip.y = 0;
    }
    if(this->clip.x > (int)this->levelW - this->clip.w){
        this->clip.x = (int)this->levelW - this->clip.w;
    }
    if(this->clip.y > (int)this->levelH - this->clip.h){
        this->clip.y = (int)this->levelH - this->clip.h;
    }
}

void Camera::setPlayerXY(double x_, double y_){
    this->playerX = x_;
    this->playerY = y_;
}

void Camera::setPlayerWH(unsigned int width_, unsigned int height_){
    this->playerW = width_;
    this->playerH = height_;
}

void Camera::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

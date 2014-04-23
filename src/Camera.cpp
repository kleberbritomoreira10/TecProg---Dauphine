#include "Camera.h"
#include "Configuration.h"

Camera::Camera():
    playerX(0.0),
    playerY(0.0),
    playerW(0),
    playerH(0),
    levelW(0),
    levelH(0),
    clip{0, 0, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()}
{
    /// @todo If the player changes the resolution, so should the clip. (?)
}

Camera::~Camera(){

}

void Camera::update(){
    updatePosition();
}

SDL_Rect& Camera::getClip(){
    return this->clip;
}

void Camera::updatePosition(){
    this->clip.x = (this->playerX + this->playerW / 2) - (this->clip.w / 2);
    this->clip.y = (this->playerY + this->playerH / 2) - (this->clip.h / 2);

    // Left wall.
    if(this->clip.x < 0){
        this->clip.x = 0;
    }
    // Right wall.
    else if(this->clip.x > (int)this->levelW - this->clip.w){
        this->clip.x = (int)this->levelW - this->clip.w;
    }
    // Top wall.
    if(this->clip.y < 0){
        this->clip.y = 0;
    }
    // Bottom wall.
    else if(this->clip.y > (int)this->levelH - this->clip.h){
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

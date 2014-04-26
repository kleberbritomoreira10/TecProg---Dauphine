#include "Animation.h"

Animation::Animation(int posX_, int posY_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool isLoop_):
	posX(posX_),
	posY(posY_),
	spriteWidth(spriteWidth_),
	spriteHeight(spriteHeight_),
	numberOfImages(numberOfImages_),
	isLoop(isLoop_),
	totalElapsedTime(0)
{

}

Animation::~Animation(){

}

void Animation::update(SDL_Rect *clip, int dt_, double deltaT_){

	//Verifica se mudou frame
    this->totalElapsedTime += dt_;
    if(this->totalElapsedTime >= (int) deltaT_) {
        this->totalElapsedTime -= (int) deltaT_;
        this->posX += 1;
        if(this->isLoop){
        	if(this->posX >= this->numberOfImages){
        		this->posX= 0;
        	}
    	}
    	else {
    		if(this->posX >= this->numberOfImages){
        		this->posX -= 1;
        	}
    	}
    }

   	int positionX_ = this->posX * this->spriteWidth;
	int positionY_ = this->posY * this->spriteHeight;

    clip->x = positionX_;
	clip->y = positionY_;
	clip->w = this->spriteWidth;
	clip->h = this->spriteHeight;

}
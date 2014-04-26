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

	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	bool endOfAnimation = (this->posX + 1) >= this->numberOfImages;

	// Verifica se mudou frame.
    this->totalElapsedTime += dt_;
    if(this->totalElapsedTime >= (int) deltaT_) {
        this->totalElapsedTime -= (int) deltaT_;
        this->posX += 1;
        if(this->isLoop){
        	if(endOfAnimation){
        		this->posX= 0;
        	}
    	}
    	else {
    		if(endOfAnimation){
        		this->posX -= 1;
        	}
    	}
    }

   	int positionX_ = this->posX * this->spriteWidth;
	int positionY_ = this->posY * this->spriteHeight;
	updateClip(clip, positionX_, positionY_, this->spriteWidth, this->spriteHeight);
}

void Animation::updateClip(SDL_Rect *clip, int positionX_, int positionY_, int spriteWidth_, int spriteHeight_ ){
	clip->x = positionX_;
	clip->y = positionY_;
	clip->w = spriteWidth_;
	clip->h = spriteHeight_;
}
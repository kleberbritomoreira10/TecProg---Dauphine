#include "Animation.h"
#include "Logger.h"

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

void Animation::setParameters(int posX_, int posY_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool isLoop_){
	this->posX = posX_;
	this->posY = posY_;
	this->spriteWidth = spriteWidth_;
	this->spriteHeight = spriteHeight_;
	this->numberOfImages = numberOfImages_;
	this->isLoop = isLoop_;
}

void Animation::update(SDL_Rect *clip, int dt_, double totalTime_){

	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	bool endOfAnimation = (this->posX + 1) >= this->numberOfImages;

	int deltaT_ = totalTime_/ this->numberOfImages;

	Logger::log("position X: " + std::to_string(this->posX));

	// Verifica se mudou frame.
    this->totalElapsedTime += dt_;
    if(this->totalElapsedTime >= deltaT_) {
        this->totalElapsedTime -= deltaT_;
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
#include "Animation.h"
#include "Logger.h"

Animation::Animation(int x_, int y_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool loop_):
	x(x_),
	y(y_),
	spriteWidth(spriteWidth_),
	spriteHeight(spriteHeight_),
	numberOfImages(numberOfImages_),
	loop(loop_),
	totalElapsedTime(0)
{

}

Animation::~Animation(){

}

void Animation::update(SDL_Rect& clip, double dt_, double totalTime_){

	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	bool endOfAnimation = (this->x + 1) >= this->numberOfImages;

	int deltaT_ = (int)(totalTime_ / this->numberOfImages);

	// Verifica se mudou frame.
    this->totalElapsedTime += (int)dt_;

    if(this->totalElapsedTime >= deltaT_) {
        this->totalElapsedTime -= deltaT_;
        this->x += 1;
        if(this->loop){
        	if(endOfAnimation){
        		this->x= 0;
        	}
    	}
    	else {
    		if(endOfAnimation){
        		this->x -= 1;
        	}
    	}
    }

   	int positionX_ = this->x * this->spriteWidth;
	int positionY_ = this->y * this->spriteHeight;
	updateClip(clip, positionX_, positionY_, this->spriteWidth, this->spriteHeight);
}

void Animation::updateClip(SDL_Rect& clip, int positionX_, int positionY_, int spriteWidth_, int spriteHeight_ ){
	clip.x = positionX_;
	clip.y = positionY_;
	clip.w = spriteWidth_;
	clip.h = spriteHeight_;
}
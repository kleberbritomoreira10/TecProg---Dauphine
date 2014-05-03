#include "Animation.h"
#include "Logger.h"

Animation::Animation(const int x_, const int y_, const int spriteWidth_,
	const int spriteHeight_, const int numberOfImages_, const bool loop_) :

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

void Animation::update(SDL_Rect& clip, const double dt_, const double totalTime_){

	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	const bool endOfAnimation = (this->x + 1) >= this->numberOfImages;

	const int deltaT = (int)(totalTime_ / this->numberOfImages);

	// Check if the frame has changed.
    this->totalElapsedTime += (int)dt_;

    if(this->totalElapsedTime >= deltaT) {
        this->totalElapsedTime -= deltaT;
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

   	const int positionX_ = this->x * this->spriteWidth;
	const int positionY_ = this->y * this->spriteHeight;
	updateClip(clip, positionX_, positionY_);
}

void Animation::updateClip(SDL_Rect& clip, const int x_, const int y_){
	clip.x = x_;
	clip.y = y_;
	clip.w = this->spriteWidth;
	clip.h = this->spriteHeight;
}
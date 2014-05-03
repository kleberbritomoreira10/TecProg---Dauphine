#ifndef INCLUDE_ANIMATION_H
#define INCLUDE_ANIMATION_H

#include "SDLWrapper.h"

class Animation{

	public:
		Animation(int posX_ = 0, int posY_ = 0, int spriteWidth_ = 229, int spriteHeight_ = 229, int numberOfImages_ = 11, bool isLoop_ = true);
		~Animation();

		void setParameters(int posX_, int posY_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool isLoop_);
		void update(SDL_Rect& clip, int dt_, double totalTime_);


	private:
		void updateClip(SDL_Rect& clip, int positionX_, int positionY_, int spriteWidth_, int spriteHeight_ );

		int posX;
		int posY;
		int spriteWidth;
		int spriteHeight;
		int numberOfImages;
		bool isLoop;
		int totalElapsedTime;

};

#endif //INCLUDE_ANIMATION_H
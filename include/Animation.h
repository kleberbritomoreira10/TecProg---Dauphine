#ifndef INCLUDE_ANIMATION_H
#define INCLUDE_ANIMATION_H

#include "SDLWrapper.h"

class Animation{

	public:
		Animation(int x_, int y_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool loop_);
		~Animation();

		void update(SDL_Rect& clip, double dt_, double totalTime_);

	private:
		void updateClip(SDL_Rect& clip, int positionX_, int positionY_, int spriteWidth_, int spriteHeight_ );

		int x;
		int y;
		int spriteWidth;
		int spriteHeight;
		int numberOfImages;
		bool loop;
		int totalElapsedTime;

};

#endif //INCLUDE_ANIMATION_H
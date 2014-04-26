#ifndef INCLUDE_ANIMATION_H
#define INCLUDE_ANIMATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animation{

	public:

		Animation(int posX_, int posY_, int spriteWidth_, int spriteHeight_, int numberOfImages_, bool isLoop_);

		~Animation();

		void update(SDL_Rect *clip, int dt_, double deltaT_);

		void updateClip(SDL_Rect *clip, int positionX_, int positionY_, int spriteWidth_, int spriteHeight_ );

		int posX;
		int posY;
		int spriteWidth;
		int spriteHeight;
		int numberOfImages;
		bool isLoop;

	private:
		int totalElapsedTime;

};

#endif //INCLUDE_ANIMATION_H
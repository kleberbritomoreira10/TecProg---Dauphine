#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DTexture.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 780;

const int FPS = 30;

class Game {

	public:
		Game();
		~Game();

		void runGame();

		SDL_Window *window;
		SDL_Renderer *renderer;
		DTexture texture;
		SDL_Event eventHandler;

		bool isRunning;

};

#endif
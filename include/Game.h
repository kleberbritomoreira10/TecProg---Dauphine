#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DTexture.h"

const ushort SCREEN_WIDTH = 1024;
const ushort SCREEN_HEIGHT = 780;

const ushort FPS = 30;

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
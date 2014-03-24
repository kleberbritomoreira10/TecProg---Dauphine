#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"

// TODO: put these somewhere else.
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 30;

class Game {

	public:
		/* Creates the window and the renderer. */
		Game();
		/* Destroys the window and the renderer. */
		~Game();

		/* Main game loop. */
		void runGame();

		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event eventHandler;

		bool isRunning;

};

#endif //INCLUDE_GAME_H

#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"
#include "Window.h"

class Game {

	public:
		/* Creates the window and the renderer. */
		Game(Window *lWindow);
		/* Destroys the window and the renderer. */
		~Game();

		/* Main game loop. */
		void runGame();

		SDL_Event eventHandler;
		FPSmanager fpsManager;

		bool isRunning;

	private:
		Window *gameWindow;

};

#endif //INCLUDE_GAME_H

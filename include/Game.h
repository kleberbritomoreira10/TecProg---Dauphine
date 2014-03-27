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
		
		/* Update the game */
		void update(double dt);
		
		/* Main game loop. */
		void runGame();

		FPSmanager fpsManager;

		bool isRunning;
		
		double dt;
		
		int x;
		
		double lastTime;
		double now;

	private:
		Window *gameWindow;

};

#endif //INCLUDE_GAME_H

#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"
#include "Window.h"
#include "State.h"

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game. Controls the current state.
*/
class Game {

	public:
		/**
		* The constructor.
		* Sets the game window and tells the game that it is OK to begin looping. Also, it begins the FPS manager.
		* @param window_ : a created Window.
		* @note If the Window parameter is null, the game will not begin.
		*/
		Game(Window *window_);

		/**
		* The destructor.
		* Destroys the game's Window, and make sure the main loop stops.
		*/
		~Game();
		
		/**
		* The main game loop.
		* Orders the game structure, such as inputs, updates, and rendering.
		*/
		void runGame();
		
		/**
		* Tell the game to quit.
		* Sets the isRunning attribute to false.
		*/
		void signalQuit();
		
	private:
		Window *window; /**< The game Window. */
		bool isRunning; /**< Whether the game is currently running/looping or not. */		
		State *currentState; /**< The current state, which the game is in. */
		FPSmanager fpsManager; /**< The FPSManager from SDL2_GFX. Handles the framerate capping. */

};

#endif //INCLUDE_GAME_H

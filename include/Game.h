#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"
#include "Window.h"
#include "State.h"

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/
class Game {

	public:
		/**
		* The constructor.
		* Sets the game window and tells the game that it is OK to begin looping. Also, it
		* 	begins the FPS manager.
		* @param window_ : a created Window.
		* @note If the Window parameter is null, the game will not begin.
		*/
		Game(Window* window_);

		/**
		* The destructor.
		* Destroys the game's Window and states, and unloads current state.
		*/
		~Game();
		
		/**
		* The main game loop.
		* Orders the game structure, such as inputs, updates, and rendering.
		*/
		void runGame();

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		static void initializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		static void destroyStates();

		/**
		* Sets the current game state.
		* @see State::load()
		* @see State::unload()
		* @param state_ : The state you want to be changed into. All states are inside Game.
		*/
		static void setState(State& state_);

		static State* stateSplash; /**< The logo splash screen. First state of the game. */
		static State* levelOne; /**< First game level. */
		
	private:
		Window *window; /**< The game Window. */
		bool isRunning; /**< Whether the game is currently running/looping or not. */		
		FPSmanager fpsManager; /**< The FPSManager from SDL2_GFX. Handles the framerate
			capping. */
		static State* currentState; /**< The current state, which the game is in. */

};

#endif //INCLUDE_GAME_H

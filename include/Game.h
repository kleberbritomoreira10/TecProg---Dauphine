#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"
#include "Window.h"
#include "StateGame.h"

#include "AudioHandler.h"
#include "InputHandler.h"

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/
class Game {

	public:
		/**
		*
		*
		*/
		static Game& instance();

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
		* @see StateGame::load()
		* @see StateGame::unload()
		* @param state_ : The state you want to be changed into. All states are inside Game.
		*/
		static void setState(StateGame& state_);

		static StateGame* stateSplash; /**< The logo splash screen. First state of the game. */
		static StateGame* levelOne; /**< First game level. */
		static StateGame* menu;

		AudioHandler& getAudioHandler();
		std::array<bool, GameKeys::MAX> getInput();

	private:
		/**
		* The constructor.
		* Sets the game window and tells the game that it is OK to begin looping. Also, it
		* 	begins the FPS manager.
		* @param window_ : a created Window.
		* @note If the Window parameter is null, the game will not begin.
		*/
		Game();

		Window *window; /**< The game Window. */
		bool isRunning; /**< Whether the game is currently running/looping or not. */		
		FPSmanager fpsManager; /**< The FPSManager from SDL2_GFX. Handles the framerate
			capping. */

		AudioHandler* audioHandler;
		InputHandler* inputHandler;

		static StateGame* currentState; /**< The current state, which the game is in. */

};

#endif //INCLUDE_GAME_H

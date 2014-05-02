#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "SDLWrapper.h"
#include "Window.h"
#include "StateGame.h"

#include <map>
#include <memory>

#include "AudioHandler.h"
#include "InputHandler.h"
#include "ResourceManager.h"

/**
* Main structure class for the game.
* Contains all the necessary functionalities to loop and update the game.
* 	Is the state machine (controls current state), contains all the different possible states.
*/
class Game {

	public:
		typedef std::shared_ptr<StateGame> StateGamePtr;

		enum GStates : uint8_t {
			SPLASH = 0,
			MENU,
			LEVEL_ONE
		};

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
		* Sets the current game state.
		* @see StateGame::load()
		* @see StateGame::unload()
		* @param state_ : The state you want to be changed into. All states are inside Game.
		*/
		void setState(GStates state_);

		//static StateGame* stateSplash; /**< The logo splash screen. First state of the game. */
		//static StateGame* levelOne; /**< First game level. */
		//static StateGame* menu;

		AudioHandler& getAudioHandler();
		std::array<bool, GameKeys::MAX> getInput();
		ResourceManager& getResources();

	private:
		/**
		* The constructor.
		* Sets the game window and tells the game that it is OK to begin looping. Also, it
		* 	begins the FPS manager.
		* @param window_ : a created Window.
		* @note If the Window parameter is null, the game will not begin.
		*/
		Game();

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		void initializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		void destroyStates();

		Window *window; /**< The game Window. */
		bool isRunning; /**< Whether the game is currently running/looping or not. */		

		AudioHandler* audioHandler;
		InputHandler* inputHandler;
		ResourceManager* resourceManager;

		StateGamePtr currentState; /**< The current state, which the game is in. */

		std::map<GStates, StateGamePtr> statesMap;

		FPSmanager fpsManager; /**< The FPSManager from SDL2_GFX. Handles the framerate
			capping. */


};

#endif //INCLUDE_GAME_H

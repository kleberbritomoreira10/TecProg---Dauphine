#ifndef INCLUDE_INPUTHANDLER_H
#define INCLUDE_INPUTHANDLER_H

#include "SDLWrapper.h"
#include "Game.h"
#include "InputKeys.h"

#include <array>
using std::array;

/**
* Handles player input.
* Using SDL event handling, recieves the player input accordingly.
*/
class InputHandler {

	public:

		static InputHandler* getInstance();
		
		/**
		* The destructor.
		* Sets the member data 'Game' back to null.
		*/
		~InputHandler();

		/**
		* Handles the input.
		* Detects the pending events, and handles them appropriately.
		*/
		void handleInput();

		/**
		* @return The keyStates attribute.
		*/
		array<bool, GameKeys::MAX> getKeyStates();

		/**
		* @return If a quit signal was recieved or not.
		*/
		bool signalQuit();

	private:

		/**
		* The constructor.
		* By setting the game to recieve input from, creates the input handler.
		* @param game_ : the game to detect input from.
		* @note If the Game parameter is null, will warn that game will have no input.
		*/
		InputHandler();

		static InputHandler* instance;

		array<bool, GameKeys::MAX> keyStates; /**< Boolean array that controls which keys are pressed or not. */
		SDL_Event eventHandler; /**< SDL internal event handler. */
		bool quit;

};

#endif //INCLUDE_INPUTHANDLER_H

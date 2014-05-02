#ifndef INCLUDE_INPUTHANDLER_H
#define INCLUDE_INPUTHANDLER_H

#include "SDLWrapper.h"
#include "InputKeys.h"
#include "ControllerHandler.h"

#include <array>

/**
* Handles player input.
* Using SDL event handling, recieves the player input accordingly.
*/
class InputHandler {

	public:
		/**
		* The constructor.
		* Used to create the input handler instance.
		*/
		InputHandler();
		
		/**
		* The destructor.
		* Deletes the InputHandler instance.
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
		std::array<bool, GameKeys::MAX> getKeyStates();

		/**
		* @return If a quit signal was recieved or not.
		*/
		bool signalQuit();

	private:
		ControllerHandler* controllerHandler;
		std::array<bool, GameKeys::MAX> keyStates; /**< Boolean array that controls which keys are
			pressed or not. */
		SDL_Event sdlEvent; /**< SDL internal event structure. */
		bool quit; /**< If the quit signal was recieved or not. */

};

#endif //INCLUDE_INPUTHANDLER_H

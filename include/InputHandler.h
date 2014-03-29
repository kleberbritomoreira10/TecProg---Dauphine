#ifndef INCLUDE_INPUTHANDLER_H
#define INCLUDE_INPUTHANDLER_H

#include "Game.h"

/**
* Handles player input.
* Using SDL event handling, recieves the player input accordingly.
*/
class InputHandler {

	public:
		/**
		* The constructor.
		* By setting the game to recieve input from, creates the input handler.
		* @param lGame : the game to detect input from.
		* @note If the lGame parameter is null, will warn that game will have no input.
		*/
		InputHandler(Game *lGame);
		
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

	private:
		SDL_Event eventHandler; /**< SDL internal event handler. */
		Game *game; /**< The Game to recieve input from. */

};

#endif //INCLUDE_INPUTHANDLER_H

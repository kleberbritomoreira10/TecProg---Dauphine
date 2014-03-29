#ifndef INCLUDE_INPUT_H
#define INCLUDE_INPUT_H

#include "Game.h"

class Input {

	public:
		/**
		* The constructor.
		* Creates the input handler for the game.
		* @params game : the game to detect input from.
		*/
		Input(Game *lGame);
		
		/**
		* The destructor.
		* Destroys the created input handler.
		*/
		~Input();

		/**
		* Handles the input.
		* Detects the pending events, and handles them appropriately.
		*/
		void handleInput();		

	private:
		SDL_Event eventHandler;
		Game *game;

};

#endif //INCLUDE_INPUT_H

#ifndef INCLUDE_INPUT_H
#define INCLUDE_INPUT_H

#include "Game.h"

class Input {

	public:
		/* Creates the game input. */
		Input();

		/* Gets the inputs. */
		void input(Game *game);

		int pendingEvent;
		SDL_Event eventHandler;

	private:
		Game *game;

};

#endif //INCLUDE_GAME_H

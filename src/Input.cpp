#include "Input.h"
#include <stdio.h>

Input::Input(){}

void Input::input(Game *game){
	// Event handling.
	int pendingEvent = 0;
	do{
		pendingEvent = SDL_PollEvent(&this->eventHandler);
		switch(this->eventHandler.type){
			// Close button.
			case SDL_QUIT:
				game->isRunning = false;
				break;
			case SDL_KEYDOWN:
				// Nested switch :( for the keydown inputs.
				switch(this->eventHandler.key.keysym.sym){
					case SDLK_ESCAPE:
						game->isRunning = false;
					default:
						break;
				}
					break;
			default:			
				break;
		}
	}while(pendingEvent != 0);
}



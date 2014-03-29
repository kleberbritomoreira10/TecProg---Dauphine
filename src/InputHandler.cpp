#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler(Game *lGame){
	this->game = lGame;

	if(this->game == nullptr){
		Logger::warning("Null game passed to input handler. Game will have no input.");
	}
}

InputHandler::~InputHandler(){
	this->game = nullptr;
}

void InputHandler::handleInput(){
	// Event handling.
	int pendingEvent = 0;
	do{
		pendingEvent = SDL_PollEvent(&this->eventHandler);
		switch(this->eventHandler.type){
			// Close button.
			case SDL_QUIT:
				this->game->isRunning = false;
				break;
			case SDL_KEYDOWN:
				// Nested switch :( for the keydown inputs.
				switch(this->eventHandler.key.keysym.sym){
					case SDLK_ESCAPE:
						this->game->isRunning = false;
					default:
						break;
				}
					break;
			default:			
				break;
		}
	} while(pendingEvent != 0);
}

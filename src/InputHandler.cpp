#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler(Game *game_){
	this->game = game_;
	for(int i=0; i<GK_MAX; i++)
		this->keyState[i] = false;

	if(this->game == nullptr){
		Logger::warning("Null game passed to input handler. Game will have no input.");
	}
}

InputHandler::~InputHandler(){
	this->game = nullptr;
}

void InputHandler::handleInput(){
	int pendingEvent = 0;
	do{
		pendingEvent = SDL_PollEvent(&this->eventHandler); 
		
		// On keydown.
		if(this->eventHandler.type == SDL_KEYDOWN){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP: // Jump.
					this->keyState[GK_UP] = true;
					break;
				case SDLK_LEFT: // Move left.
					this->keyState[GK_LEFT] = true;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyState[GK_RIGHT] = true;
					break;
				default:
					break;

			}
		}
		if(this->eventHandler.type == SDL_KEYUP){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP:
					this->keyState[GK_UP] = false;
					break;
				case SDLK_LEFT:
					this->keyState[GK_LEFT] = false;
					break;
				case SDLK_RIGHT:
					this->keyState[GK_RIGHT] = false;
					break;
				default:
					break;
			}
		}
		
		if(this->eventHandler.type == SDL_QUIT){
	    	this->game->isRunning = false;
	    }

	} while(pendingEvent != 0);
}

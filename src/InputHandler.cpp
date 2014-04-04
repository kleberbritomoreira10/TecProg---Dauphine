#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler(Game *lGame){
	this->game = lGame;
	int i;
	for(i=0; i<10; i++)
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
		
		if(this->eventHandler.type == SDL_KEYDOWN){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP:
					this->keyState[0] = true;
					break;
				case SDLK_LEFT:
					this->keyState[1] = true;
					break;
				case SDLK_RIGHT:
					this->keyState[2] = true;
					break;
				default:
					break;

			}
		}
		if(this->eventHandler.type == SDL_KEYUP){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP:
					this->keyState[0] = false;
					break;
				case SDLK_LEFT:
					this->keyState[1] = false;
					break;
				case SDLK_RIGHT:
					this->keyState[2] = false;
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

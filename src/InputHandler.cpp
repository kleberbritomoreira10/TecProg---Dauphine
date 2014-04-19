#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler(Game *game_) :
	game(game_)
{
	for(unsigned int i = 0; i < GameKeys::MAX; i++){
		this->keyStates[i] = false;
	}

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
					this->keyStates[GameKeys::UP] = true;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = true;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = true;
					break;
				default:
					break;

			}
		}

		// On keyup.
		else if(this->eventHandler.type == SDL_KEYUP){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP: // Jump.
					this->keyStates[GameKeys::UP] = false;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = false;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = false;
					break;
				default:
					break;
			}
		}
		
		// On window exit (X).
		else if(this->eventHandler.type == SDL_QUIT){
	    	this->game->signalQuit();
	    }

	} while(pendingEvent != 0);
}

array<bool, GameKeys::MAX> InputHandler::getKeyStates(){
	return this->keyStates;
}

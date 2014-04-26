#include "InputHandler.h"
#include "ControlWrapper.h"

InputHandler* InputHandler::instance = nullptr;

InputHandler::InputHandler() :
	quit(false)
{
	for(unsigned int i = 0; i < GameKeys::MAX; i++){
		this->keyStates[i] = false;
	}
}

InputHandler* InputHandler::getInstance(){
	if(InputHandler::instance == nullptr){
		InputHandler::instance =  new InputHandler();
	}

	return InputHandler::instance;
}

InputHandler::~InputHandler(){
	delete InputHandler::instance;
}

void InputHandler::handleInput(){

	int pendingEvent = 0;
	
	SDL_GameController* _gameController = SDL_GameControllerOpen(0);

	// ControlWrapper::decide();

	do{
		pendingEvent = SDL_PollEvent(&this->eventHandler); 

		// On keydown.
		if(this->eventHandler.type == SDL_KEYDOWN){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					this->keyStates[GameKeys::UP] = true;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = true;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = true;
					break;
				case SDLK_c: // Roll.
					this->keyStates[GameKeys::ROLL] = true;
					break;
				default:
					break;
			}
		}

		// On keyup.
		else if(this->eventHandler.type == SDL_KEYUP){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					this->keyStates[GameKeys::UP] = false;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = false;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = false;
					break;
				case SDLK_c: // Roll.
					this->keyStates[GameKeys::ROLL] = false;
					break;
				default:
					break;
			}
		}
		
		//On window exit (X).
		else if(this->eventHandler.type == SDL_QUIT){
	    	this->quit = true;
	    }

	} while(pendingEvent != 0);
}

array<bool, GameKeys::MAX> InputHandler::getKeyStates(){
	return this->keyStates;
}

bool InputHandler::signalQuit(){
	return this->quit;
}

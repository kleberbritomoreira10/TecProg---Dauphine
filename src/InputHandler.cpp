#include "InputHandler.h"

InputHandler::InputHandler() :
	quitFlag(false)
{
	for(unsigned int i = 0; i < GameKeys::MAX; i++){
		this->keyStates[i] = false;
	}

	// Opens controller handling.
	this->controllerHandler = new ControllerHandler();
}

InputHandler::~InputHandler(){
	if(this->controllerHandler != nullptr){
		delete this->controllerHandler;
		this->controllerHandler = nullptr;
	}	
}

void InputHandler::handleInput(){

	int pendingEvent = 0;

	do{
		pendingEvent = SDL_PollEvent(&this->sdlEvent); 

		if(this->sdlEvent.type == SDL_CONTROLLERBUTTONDOWN
			|| this->sdlEvent.type == SDL_CONTROLLERBUTTONUP){
			
			this->controllerHandler->handleInput(this->sdlEvent);
		}

		// On keydown.
		if(this->sdlEvent.type == SDL_KEYDOWN){
			switch(this->sdlEvent.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					this->keyStates[GameKeys::SPACE] = true;
					break;
				case SDLK_UP: // UP.
					this->keyStates[GameKeys::UP] = true;
					break;
				case SDLK_DOWN: // DOWN.
					this->keyStates[GameKeys::DOWN] = true;
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
				case SDLK_a: // Roll.
					this->keyStates[GameKeys::A] = true;
					break;
				case SDLK_d: // Roll.
					this->keyStates[GameKeys::D] = true;
					break;
				case SDLK_ESCAPE: // ESC
					this->keyStates[GameKeys::ESCAPE] = true;
					break;
				default:
					break;
			}
		}

		// On keyup.
		else if(this->sdlEvent.type == SDL_KEYUP){
			switch(this->sdlEvent.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					this->keyStates[GameKeys::SPACE] = false;
					break;
				case SDLK_UP: // UP.
					this->keyStates[GameKeys::UP] = false;
					break;
				case SDLK_DOWN: // DOWN.
					this->keyStates[GameKeys::DOWN] = false;
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
				case SDLK_a: // Roll.
					this->keyStates[GameKeys::A] = false;
					break;
				case SDLK_d: // Roll.
					this->keyStates[GameKeys::D] = false;
					break;
				case SDLK_ESCAPE: // ESC
					this->keyStates[GameKeys::ESCAPE] = true;
					break;
				default:
					break;
			}
		}
		
		//On window exit (X).
		else if(this->sdlEvent.type == SDL_QUIT){
	    	signalExit();
	    }

	} while(pendingEvent != 0);
}

std::array<bool, GameKeys::MAX> InputHandler::getKeyStates(){
	return this->keyStates;
}

bool InputHandler::isQuitFlag(){
	return this->quitFlag;
}

void InputHandler::signalExit(){
	this->quitFlag = true;
}

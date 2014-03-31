#include "InputHandler.h"
#include "Logger.h"
#include <stdio.h>

static const int VEL = 10;

InputHandler::InputHandler(Game *lGame){
	this->game = lGame;
	this->pVelX = 0;
	this->pVelY = 0;

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
		 // If a key was pressed.
		if( this->eventHandler.type == SDL_KEYDOWN && this->eventHandler.key.repeat == 0 )
	    {
	        // Adjust the velocity.
	        switch( this->eventHandler.key.keysym.sym )
	        {
	            case SDLK_UP: pVelY -= VEL; break;
	            case SDLK_DOWN: pVelY += VEL; break;
	            case SDLK_LEFT: pVelX -= VEL; break;
	            case SDLK_RIGHT: pVelX += VEL; break;
	        }
	    }
	    // If a key was released.
	    else if( this->eventHandler.type == SDL_KEYUP && this->eventHandler.key.repeat == 0 )
	    {
	        // Adjust the velocity.
	        switch( this->eventHandler.key.keysym.sym )
	        {
	            case SDLK_UP: pVelY += VEL; break;
	            case SDLK_DOWN: pVelY -= VEL; break;
	            case SDLK_LEFT: pVelX += VEL; break;
	            case SDLK_RIGHT: pVelX -= VEL; break;
	        }
	    }
	    if( this->eventHandler.type == SDL_QUIT ){
	    	this->game->isRunning = false;
	    }
	} while(pendingEvent != 0);
}

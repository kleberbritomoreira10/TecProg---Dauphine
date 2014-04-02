#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler(Game *lGame, Player *lPlayer){
	this->game = lGame;
	this->moveRightCommand = new Command(lPlayer, &Player::moveRight);
	this->moveLeftCommand = new Command(lPlayer, &Player::moveLeft);
	this->jumpCommand = new Command(lPlayer, &Player::jump);

	if(this->game == nullptr){
		Logger::warning("Null game passed to input handler. Game will have no input.");
	}
}

InputHandler::~InputHandler(){
	this->game = nullptr;
}

Command* InputHandler::handleInput(){
	int pendingEvent = 0;
	do{
		pendingEvent = SDL_PollEvent(&this->eventHandler); 
		
		if(this->eventHandler.type == SDL_KEYDOWN){
			switch(this->eventHandler.key.keysym.sym){
				case SDLK_UP:
					return this->jumpCommand;
					break;
				case SDLK_LEFT:
					return this->moveLeftCommand;
					break;
				case SDLK_RIGHT:
					return this->moveRightCommand;
					break;
				default:
					return nullptr;
					break;
			}
		}
		else if(this->eventHandler.type == SDL_QUIT){
	    	this->game->isRunning = false;
	    }

	} while(pendingEvent != 0);

	return nullptr;
}

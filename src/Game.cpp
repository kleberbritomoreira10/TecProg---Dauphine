#include "Game.h"
#include "Logger.h"

#include "Sprite.h"

Game::Game(Window *lGameWindow){
	this->gameWindow = lGameWindow;
}

Game::~Game(){
	// Destroys the Window.
	this->gameWindow->destroy();
}

void Game::runGame(){
	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(gameWindow->renderer);
	bool loadedSprite = sprite->loadFrom("res/dots.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite.");
	}

	// Main game loop.
	while(this->isRunning){

		// Event handling.
		int pendingEvent = 0;
		do{
			pendingEvent = SDL_PollEvent(&this->eventHandler);
			switch(this->eventHandler.type){
				// Close button.
				case SDL_QUIT:
					this->isRunning = false;
					break;
				case SDL_KEYDOWN:
					// Nested switch :( for the keydown inputs.
					switch(this->eventHandler.key.keysym.sym){
						case SDLK_ESCAPE:
							this->isRunning = false;
						default:
							break;
					}

					break;
				default:
					break;
			}
		}while(pendingEvent != 0);

		// Sets the draw color and clears the screen.
		gameWindow->clear();

		// Render the example sprite.
		sprite->render(0, 0, nullptr);

		// Renders the gameWindow.
		gameWindow->render();
	}
}

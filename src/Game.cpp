#include "Game.h"
#include "Logger.h"

#include "Sprite.h"

Game::Game(){
	// Creates the Game window.
	this->window = SDL_CreateWindow("Dauphine", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(this->window != nullptr){

		//Creates the Game renderer.
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		if(this->renderer != nullptr){

				// Game is successfully loaded.
				this->isRunning = true;
		}
		else{
			Logger::errorSDL("Renderer could not be created.", SDL_GetError());
		}
	}
	else{
		Logger::errorSDL("Window failed to be created.", SDL_GetError());
	}

}

Game::~Game(){
	// Destroys the Game renderer.
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;

	// Destroys the Game window.
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
}

void Game::runGame(){
	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->renderer);
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

		// Set color and clear screen.
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render the example sprite.
		sprite->render(0, 0, nullptr);

		// Update screen.
		SDL_RenderPresent(renderer);
	}
}

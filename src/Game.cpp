#include "Game.h"
#include "Logger.h"

#include "Sprite.h"

Game::Game(Window *lGameWindow){
	if(lGameWindow != nullptr){
		this->gameWindow = lGameWindow;
		this->isRunning = true;

		// TODO: extract this to a method. Possibly a framerate wrapper, to work with dt.
		// Initializes the SDL2_GFX framerate control.
		SDL_initFramerate(&this->fpsManager);
		int framerateSet = SDL_setFramerate(&this->fpsManager, DESIRED_FPS);
		if(framerateSet == 0){
			Logger::log("Successfully started the framerate manager.");
		}
		else{
			Logger::warning("Failed to start the framerate manager.");
		}
	}
	else{
		this->gameWindow = nullptr;
		this->isRunning = false;
		Logger::warning("Game window is null. Game will not run.");
	}
}

Game::~Game(){
	// Destroys the Window.
	this->gameWindow->destroy();
}

void Game::runGame(){
	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->gameWindow->renderer);
	bool loadedSprite = sprite->loadFrom("res/hdimg.png");
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

		// Delays the framerate, if necessary.
		SDL_framerateDelay(&this->fpsManager);

	}

}

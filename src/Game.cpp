#include "Game.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Player.h"
#include "Logger.h"
#include "Configuration.h"

Game::Game(Window *window_){
	if(window_ != nullptr){
		this->gameWindow = window_;
		this->isRunning = true;
		
		/// @todo Separate the FPS manager things into another class, probably a FPSWrapper.
		// Initializes the SDL2_GFX framerate control.
		SDL_initFramerate(&this->fpsManager);
		const int framerateSet = SDL_setFramerate(&this->fpsManager, Configuration::FRAMERATE);
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
		Logger::error("Game window is null. Game will not run.");
	}
}

Game::~Game(){
	// Destroys the Window.
	this->gameWindow->destroy();
	this->gameWindow = nullptr;
	this->isRunning = false;
}

void Game::runGame(){
	/// @todo Remove all of the example code from inside this method.

	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->gameWindow->renderer);
	bool loadedSprite = sprite->loadFrom("res/player.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite.");
	}

	// Creating the player example.
	Player player(300, 300, sprite);

	// Creating the input handler.
	InputHandler gameInput(this);
	
	/// @todo Handle all of this DT issues from the FPSWrapper. Also, SDL_GetTicks returns Uint32, not a double.
	// Get the first game time.
	double lastTime = SDL_GetTicks();
	
	// This is the main game loop.
	while(this->isRunning){

		// Clearing the screen.
		gameWindow->clear();
		
		// Recieving the input.
		gameInput.handleInput();

		// Calculations to get the delta time.
		double now = SDL_GetTicks();
		double dt = (now - lastTime)/1000.0;
		lastTime = now;

		// Updating the game.
		player.updateInput(gameInput.keyState);
		player.update(dt);

		// Rendering the game.
		player.render();
		gameWindow->render();
		
		// Delays the framerate, if necessary.
		SDL_framerateDelay(&this->fpsManager);

	}

}

void Game::update(double dt_){
	/// @todo Implement this method.
}

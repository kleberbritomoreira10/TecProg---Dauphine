#include "Game.h"
#include "Logger.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Player.h"

Game::Game(Window *lGameWindow){
	if(lGameWindow != nullptr){
		this->gameWindow = lGameWindow;
		this->isRunning = true;
		
		/// @todo Separate the FPS manager things into another class, probably a FPSWrapper.
		// Initializes the SDL2_GFX framerate control.
		const int DESIRED_FPS = 60;

		SDL_initFramerate(&this->fpsManager);
		const int framerateSet = SDL_setFramerate(&this->fpsManager, DESIRED_FPS);
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

	// Creating the input handler	
	InputHandler gameInput(this, &player);
	
	/// @todo Handle all of this DT issues from the FPSWrapper. Also, SDL_GetTicks returns Uint32, not a double.
	// Get the first game time.
	double lastTime = SDL_GetTicks();
	
	// Main game loop.
	while(this->isRunning){

		// Sets the draw color and clears the screen.
		gameWindow->clear();
		
		Command *command = gameInput.handleInput();
		if(command != nullptr){
			command->execute();
		}

		// get the current time. 
		double now = SDL_GetTicks();
		// Diff of last time and current time.
		double dt = (now - lastTime)/1000.0;
		// update the last time.
		lastTime = now;

		// Updating the game.	
		player.update(dt);
		// Renders the player.
		player.render();


		// Renders the gameWindow.
		gameWindow->render();
		

		// Delays the framerate, if necessary.
		SDL_framerateDelay(&this->fpsManager);

	}

}

void Game::update(double dt){
	/// @todo Implement this method.
}

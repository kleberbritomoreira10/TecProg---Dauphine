#include <stdio.h>
#include "Game.h"
#include "Logger.h"
#include <time.h>
#include "Sprite.h"
#include "Input.h"

Game::Game(Window *lGameWindow){
	if(lGameWindow != nullptr){
		this->gameWindow = lGameWindow;
		this->isRunning = true;

		//TODO: put this in a player class...
		// Position of rendering sprite
		this->x = 0;
		
		const int DESIRED_FPS = 60;

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

	// Creating the input handler	
	Input *gameInput = nullptr;
	gameInput = new Input();
	
	// Get the first game time.
	double lastTime = clock();
	
	// Main game loop.
	while(this->isRunning){

		// Sets the draw color and clears the screen.
		gameWindow->clear();
		
		// Gets the inputs.
		gameInput->input(this);
	
		// get the current time. 
		double now = clock();
		// Diff of last time and current time.
		double dt = (now - lastTime)/1000.0;
		// update the last time.
		lastTime = now;
		// Updating the game.	
		this->update(dt);

		// Render the example sprite.
		sprite->render(x, 0, nullptr);

		// Renders the gameWindow.
		gameWindow->render();

		// Delays the framerate, if necessary.
		SDL_framerateDelay(&this->fpsManager);

	}

}

void Game::update(double dt){
	// Increase sprite position
	this->x += 1*dt;
}

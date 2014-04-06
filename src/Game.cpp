#include "Game.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Player.h"
#include "FPSWrapper.h"
#include "Logger.h"
#include "Configuration.h"
#include "Camera.h"

#include <stdio.h>

Game::Game(Window *window_){
	if(window_ != nullptr){
		this->gameWindow = window_;
		this->isRunning = true;
		
		FPSWrapper::initialize(this->fpsManager);
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

	Sprite *spriteScene = nullptr;
	spriteScene = new Sprite(this->gameWindow->renderer);
	bool loadedSprite = spriteScene->loadFrom("res/scene.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite scene.");
	}

	// Just an example of Sprite loading, delete this later.
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->gameWindow->renderer);
	loadedSprite = sprite->loadFrom("res/player.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite.");
	}

	// Creating the player example.
	Player player(300, 300, sprite);
	Camera camera(0, 0, spriteScene);

	// Creating the input handler.
	InputHandler gameInput(this);
	
	// Get the first game time.
	double totalGameTime = 0.0;
	const double deltaTime = 1.0 / 60.0;
	double accumulatedTime = 0.0;

	// This is the main game loop.
	while(this->isRunning){

		const double frameTime = FPSWrapper::delay(this->fpsManager);
		accumulatedTime += frameTime;

		// Update.
		while(accumulatedTime >= deltaTime){
			gameInput.handleInput();
			camera.updateInput(gameInput.keyState);
			camera.update(deltaTime);
			player.updateInput(gameInput.keyState);
			player.update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		gameWindow->clear();
		camera.render();
		player.render();
		gameWindow->render();
		
	}

}

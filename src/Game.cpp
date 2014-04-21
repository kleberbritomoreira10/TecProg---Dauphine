#include "Game.h"
#include "InputHandler.h"
#include "Camera.h"
#include "FPSWrapper.h"
#include "Logger.h"
#include "Configuration.h"
#include "Player.h"
#include "Sprite.h"
#include "LuaScript.h"

#include "StateSplash.h"
#include "LevelOne.h"

State* Game::currentState = nullptr;
State* Game::stateSplash = nullptr;
State* Game::levelOne = nullptr;

Game::Game(Window *window_) :
	window(window_),
	isRunning(false)
{
	initializeStates();

	if(this->window != nullptr){
		this->isRunning = true;
		FPSWrapper::initialize(this->fpsManager);

		Game::currentState = Game::stateSplash;
	}
	else{
		Logger::error("Game window is null. Game will not run.");
	}
}

Game::~Game(){
	this->window->destroy();
	this->window = nullptr;
	this->isRunning = false;
}

void Game::runGame(){
	
	// Creating the input handler.
	InputHandler *inputHandler = InputHandler::getInstance();
	
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
			inputHandler->handleInput();
			array<bool, GameKeys::MAX> gameKeys = inputHandler->getKeyStates();

			// Check for a quit signal from input.
			if(inputHandler->signalQuit()){
				this->isRunning = false;
				return;
			}
			
			// State is a level (has a player).
			if(Game::currentState->getPlayer() != nullptr){
				Game::currentState->getPlayer()->updateInput(gameKeys);
			}

			Game::currentState->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();

		Game::currentState->render();

		window->render();
		
	}

}

void Game::setState(State& state_){
	/// @todo Implement the transition between states.
	Game::currentState->unload();
	Game::currentState = &state_;
	Game::currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.
	Game::stateSplash = new StateSplash();
	Game::levelOne = new LevelOne();
}

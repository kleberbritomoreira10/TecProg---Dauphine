#include "Game.h"
#include "FPSWrapper.h"

#include "Logger.h"
#include "Configuration.h"

#include <cassert>

#include "GStateSplash.h"
#include "LevelOne.h"
#include "GStateMenu.h"

StateGame* Game::currentState = nullptr;
StateGame* Game::stateSplash = nullptr;
StateGame* Game::levelOne = nullptr;
StateGame* Game::menu = nullptr;

Game& Game::instance(){
	static Game* instance = new Game();
	return *instance;
}

Game::Game() :
	window(nullptr),
	isRunning(false)
{
	Game::initializeStates();

	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	this->isRunning = true;
	FPSWrapper::initialize(this->fpsManager);

	Game::currentState = Game::stateSplash;
	Game::currentState->load();
}

Game::~Game(){
	if(Game::currentState != nullptr){
		Game::currentState->unload();
	}

	Game::destroyStates();

	if(this->audioHandler != nullptr){
		delete this->audioHandler;
	}
	if(this->inputHandler != nullptr){
		delete this->inputHandler;
	}

	if(this->window != nullptr){
		this->window->destroy();
		this->window = nullptr;
	}
}

void Game::runGame(){

	// Creating the input handler.
	this->audioHandler = new AudioHandler();
	this->inputHandler = new InputHandler();

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
			this->inputHandler->handleInput();

			// Check for a quit signal from input.
			if(this->inputHandler->signalQuit()){
				this->isRunning = false;
				return;
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

void Game::setState(StateGame& state_){
	/// @todo Implement the transition between states.
	Game::currentState->unload();
	Game::currentState = &state_;
	Game::currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.
	Game::stateSplash = new GStateSplash();
	Game::levelOne = new LevelOne();
	Game::menu = new GStateMenu();
}

void Game::destroyStates(){
	// Delete all the states in Game here.
	delete Game::stateSplash;
	delete Game::levelOne;
	delete Game::menu;
}

AudioHandler& Game::getAudioHandler(){
	return (*(this->audioHandler));
}

std::array<bool, GameKeys::MAX> Game::getInput(){
	return this->inputHandler->getKeyStates();
}

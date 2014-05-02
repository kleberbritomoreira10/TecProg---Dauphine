#include "Game.h"
#include "FPSWrapper.h"

#include "Logger.h"
#include "Configuration.h"

#include <cassert>

#include "GStateSplash.h"
#include "LevelOne.h"
#include "GStateMenu.h"

Game& Game::instance(){
	static Game* instance = new Game();
	return *instance;
}

Game::Game() :
	window(nullptr),
	isRunning(false),
	audioHandler(nullptr),
	inputHandler(nullptr),
	resourceManager(nullptr),
	currentState(nullptr),
	statesMap()
{
	initializeStates();

	this->window = new Window(Configuration::getScreenWidth(), Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	this->isRunning = true;
	FPSWrapper::initialize(this->fpsManager);

	this->currentState = this->statesMap.at(GStates::SPLASH);
	this->currentState->load();
}

Game::~Game(){
	if(this->currentState != nullptr){
		this->currentState->unload();
	}

	this->statesMap.clear();

	if(this->audioHandler != nullptr){
		delete this->audioHandler;
	}
	if(this->inputHandler != nullptr){
		delete this->inputHandler;
	}
	if(this->resourceManager != nullptr){
		delete this->resourceManager;
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
	this->resourceManager = new ResourceManager();

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

			this->currentState->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();

		this->currentState->render();

		window->render();
		
	}

}

void Game::setState(GStates state_){
	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.

	// Typedefs for all the states shared_ptr.
	typedef std::shared_ptr<GStateSplash>	SplashPtr;
	typedef std::shared_ptr<GStateMenu>		MenuPtr;
	typedef std::shared_ptr<LevelOne>		LevelOnePtr;

	// Set the shared_ptr for each state.
	SplashPtr splash = std::make_shared<GStateSplash>();
	MenuPtr menu = std::make_shared<GStateMenu>();
	LevelOnePtr levelOne = std::make_shared<LevelOne>();

	// Emplace the states pointers onto the map.
	this->statesMap.emplace(GStates::SPLASH, 	splash);
	this->statesMap.emplace(GStates::MENU,		menu);
	this->statesMap.emplace(GStates::LEVEL_ONE,	levelOne);
}

AudioHandler& Game::getAudioHandler(){
	return (*(this->audioHandler));
}

std::array<bool, GameKeys::MAX> Game::getInput(){
	return this->inputHandler->getKeyStates();
}

ResourceManager& Game::getResources(){
	return (*(this->resourceManager));
}

#include "Game.h"
#include "FPSWrapper.h"
#include "Configuration.h"
#include <cassert>

#include "GStateSplash.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelBoss.h"
#include "GStateMenu.h"
#include "GStateNewGame.h"
#include "GStateContinue.h"
#include "GStateOptions.h"
#include "GStateCredits.h"
#include "GStateGameOver.h"
#include "Sprite.h"

#include "Logger.h"

#define ADD_STATE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass())

Game& Game::instance(){
	static Game* instance = new Game();
	return *instance;
}

Game::Game() :
	isPaused(false),
	window(nullptr),
	isRunning(false),
	pauseImage(nullptr),
	audioHandler(new AudioHandler()),
	inputHandler(new InputHandler()),
	resourceManager(new ResourceManager()),
	fadeScreen(nullptr),
	currentState(nullptr),
	statesMap(),
	passedTime(0.0),
	currentSelection(PSelection::RESUME),
	selectorXPositionLeft {610, 635, 635},
	selectorYPositionLeft {400, 500, 590},
	selectorXPositionRight {880, 855, 855},
	selectorYPositionRight {400, 500, 590}
{
	initializeStates();

	this->window = new Window(Configuration::getScreenWidth(),
		Configuration::getScreenHeight(), Configuration::getWindowTitle());

	assert(this->window != nullptr && "The window should not be null!");

	this->pauseImage = getResources().get("res/images/pause_overlay.png");
	this->pauseSelector = getResources().get("res/images/cursor_regular.png");
	this->pauseSelector->setWidth(50);

	this->isRunning = true;
	FPSWrapper::initialize(this->fpsManager);
}

Game::~Game(){
	if(this->currentState != nullptr){
		this->currentState->unload();
	}

	destroyStates();

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
	this->fadeScreen = new FadeScreen();

	this->currentState = this->statesMap.at(GStates::SPLASH);
	this->currentState->load();

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

			// Check for an exit signal from input.
			if(this->inputHandler->isQuitFlag() == true){
				stop();
				return;
			}

			std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

			if(keyStates[GameKeys::ESCAPE]){
				this->isPaused = true;
			}

			if(!this->isPaused){
				this->currentState->update(deltaTime);				    
			}
			else{
				this->passedTime += deltaTime;
				updatePause();
			}


			this->fadeScreen->update(deltaTime);

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		window->clear();
		
		this->currentState->render();				    
		if(this->isPaused){
			renderPause();
		}
		this->fadeScreen->render();

		window->render();
		
	}

}

void Game::setState(const GStates state_){
	/// @todo Implement the transition between states.
	this->currentState->unload();
	this->currentState = this->statesMap.at(state_);
	this->currentState->load();
}

void Game::initializeStates(){
	// Initialize all the states in Game here.

	// Emplace the states pointers onto the map.
	ADD_STATE(SPLASH, GStateSplash);
	ADD_STATE(MENU, GStateMenu);
	ADD_STATE(NEW_GAME, GStateNewGame);
	ADD_STATE(LEVEL_ONE, LevelOne);
	ADD_STATE(LEVEL_TWO, LevelTwo);
	ADD_STATE(LEVEL_BOSS, LevelBoss);
	ADD_STATE(CONTINUE, GStateContinue);
	ADD_STATE(OPTIONS, GStateOptions);
	ADD_STATE(CREDITS, GStateCredits);
	ADD_STATE(GAMEOVER, GStateGameOver);
}

void Game::renderPause(){
	if(this->pauseImage != nullptr){
		this->pauseImage->render(0, 0, nullptr, true);

		this->pauseSelector->render(selectorXPositionLeft[currentSelection],
			selectorYPositionLeft[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);

		this->pauseSelector->render(selectorXPositionRight[currentSelection],
			selectorYPositionRight[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else{
		Log(WARN) << "No image set to display on the menu!";
	}
}

void Game::updatePause(){

	handleSelectorMenu();
}

void Game::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection < (PSelection::TOTAL - 1)){
				currentSelection++;
			}
			else{
				currentSelection = PSelection::RESUME;
			}
			this->passedTime = 0.0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection > PSelection::RESUME){
				currentSelection--;
			}
			else{
				currentSelection = (PSelection::TOTAL - 1);
			}
			this->passedTime = 0.0;
		}
	}
	else if(currentSelection == PSelection::RESUME && keyStates[GameKeys::SPACE] == true){
		this->isPaused = false;
	}

	else if(currentSelection == PSelection::SAVE && keyStates[GameKeys::SPACE] == true){
		
	}

	else if(currentSelection == PSelection::EXIT && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::MENU);
		this->isPaused = false;
	}
}

void Game::destroyStates(){
	std::map<GStates, StateGame*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
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

void Game::stop(){
	this->isRunning = false;
}

void Game::clearKeyFromInput(const GameKeys key_){
	this->inputHandler->clearKey(key_);
}

FadeScreen& Game::getFade(){
	return (*(this->fadeScreen));
}

void Game::resizeWindow(const unsigned int width_, const unsigned int height_){
	this->window->resize(width_, height_);
}

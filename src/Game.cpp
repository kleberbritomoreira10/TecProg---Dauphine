#include "Game.h"
#include "InputHandler.h"
#include "Camera.h"
#include "FPSWrapper.h"
#include "Logger.h"
#include "Configuration.h"
#include "Level.h"
#include "Player.h"
#include "Sprite.h"
#include "LuaScript.h"

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
	this->gameWindow->destroy();
	this->gameWindow = nullptr;
	this->isRunning = false;
}

void Game::runGame(){
	/// @todo Remove all of the example code from inside this method.

	// Getting information from lua script
	LuaScript luaLevel1("lua/Level1.lua");
	const string scriptPlayerSpritePath = luaLevel1.unlua_get<string>("level.player.spritePath");
	const string scriptBackgroundSpritePath = luaLevel1.unlua_get<string>("level.background.spritePath");
	const double scriptX = luaLevel1.unlua_get<double>("level.player.position.x");
	const double scriptY = luaLevel1.unlua_get<double>("level.player.position.y");

	// Just an example of Sprite loading, delete this later.
	Sprite *spriteLevelBackground = nullptr;
	spriteLevelBackground = new Sprite(this->gameWindow->renderer, scriptBackgroundSpritePath);
	const unsigned int bgWidth = spriteLevelBackground->getWidth();
	const unsigned int bgHeight = spriteLevelBackground->getHeight();

	Sprite *spritePlayer = nullptr;
	spritePlayer = new Sprite(this->gameWindow->renderer, scriptPlayerSpritePath);

	// Creating level, camera and player.
	Level level(bgWidth, bgHeight);
	Camera camera;
	Player player(scriptX, scriptY, spritePlayer);
	level.setBackground(spriteLevelBackground);
	level.setPlayer(player);
	level.setCamera(camera);


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

			player.updateInput(gameInput.keyState);
			player.update(deltaTime);

			level.update();

			camera.update();

			accumulatedTime -= deltaTime;
			totalGameTime += deltaTime;
		}

		// Render.
		gameWindow->clear();
		level.render(&camera.clip);
		player.render();
		gameWindow->render();
		
	}

}

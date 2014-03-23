#include "Game.h"
#include "Logger.h"

int main(int argc, char **argv){
	Logger::log("Starting Dauphine...");

	bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Game *game = nullptr;
		game = new Game();

		game->runGame();
	}
	else{
		Logger::error("System were not initialized.");
	}

	SDLWrapper::close();

	Logger::log("Exiting Dauphine...");
	return 0;
}

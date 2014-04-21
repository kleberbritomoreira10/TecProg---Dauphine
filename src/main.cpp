#include "Game.h"
#include "Logger.h"
#include "Configuration.h"

int main(int argc, char **argv){
	if(argc == 2 && argv[1] == std::string("-v")){
		Logger::isVerbose = true;
	}

	Logger::verbose("Starting Dauphine...");	

	bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Window window(Configuration::getScreenWidth(), Configuration::getScreenHeight(), Configuration::TITLE);

		Game *game = nullptr;
		game = new Game(&window);

		game->runGame();
	}
	else{
		Logger::error("System were not initialized.");
	}

	SDLWrapper::close();

	Logger::verbose("Exiting Dauphine...");
	return 0;
}

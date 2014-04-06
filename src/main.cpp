#include "Game.h"
#include "Logger.h"
#include "Configuration.h"

// Since argc and argv are only necessary for cross-compiling SDL_Main,
// we do this just so the compiler doesn't warn for unused arguments.
#define UNUSED(x) ((void)x)

int main(int argc, char **argv){
	Logger::log("Starting Dauphine...");

	UNUSED(argc);
	UNUSED(argv);

	bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Window window(Configuration::screenWidth, Configuration::screenHeight, Configuration::TITLE);

		Game *game = nullptr;
		game = new Game(&window);

		game->runGame();
	}
	else{
		Logger::error("System were not initialized.");
	}

	SDLWrapper::close();

	Logger::log("Exiting Dauphine...");
	return 0;
}

#include "Game.h"
#include "Logger.h"

// Since argc and argv are only necessary for cross-compiling SDL_Main,
// we do this just so the compiler doesn't warn for unused arguments.
#define UNUSED(x) ((void)x)

int main(int argc, char **argv){
	Logger::log("Starting Dauphine...");

	UNUSED(argc);
	UNUSED(argv);

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

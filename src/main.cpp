#include "Game.h"
#include "Logger.h"
#include "Player.h"

// Since argc and argv are only necessary for cross-compiling SDL_Main,
// we do this just so the compiler doesn't warn for unused arguments.
#define UNUSED(x) ((void)x)

// TODO: put these somewhere else.
// 16:10 aspect ratio, for now.
const int SCREEN_WIDTH = 192 * 5;
const int SCREEN_HEIGHT = 108 * 5;

int main(int argc, char **argv){
	Logger::log("Starting Dauphine...");

	UNUSED(argc);
	UNUSED(argv);

	bool systemsInitialized = SDLWrapper::initialize();

	if(systemsInitialized){
		Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Dauphine");

		Game *game = nullptr;
		Player *player = nullptr;
		game = new Game(&window);
		player = new Player(0,0,&game);
		game->setPlayer(&player);

		game->runGame();
	}
	else{
		Logger::error("System were not initialized.");
	}

	SDLWrapper::close();

	Logger::log("Exiting Dauphine...");
	return 0;
}

#include "Game.h"
#include "Logger.h"

int main(int argc, char **argv){

	Logger::log("Starting Dauphine...");

	Game *game;
	game = new Game();

	game->runGame();

	Logger::log("Exiting Dauphine...");

	return 0;
}
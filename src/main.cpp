#include "Game.h"
#include "Util.h"

int main(){

	log("Starting Dauphine...");

	Game *game;
	game = new Game();

	game->runGame();

	log("Exiting Dauphine...");

	return 0;
}
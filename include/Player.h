#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Game.h"

class Player {

	public:
		/**
		* The constructor.
		* Creates the player and associates it to a game.
		* @param x : position in x axis.
		* @param y : position in y axis.
		* @param game : associates the player to a game.
		*/
		Player(double x, double y, Game *lgame);
		
		/**
		* Handles the render.
		* render the player
		*/
		void render();
		
		double x;
		double y;

	private:
		Game *lgame;

};

#endif //INCLUDE_PLAYER_H

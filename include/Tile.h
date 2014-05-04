#ifndef INCLUDE_TILE_H
#define INCLUDE_TILE_H

enum TileCode : int {
	FLOOR1 = 0,
	FLOOR2,
	WALL1,
	WALL2,
	WALL3,
	WALL4,
	WALL5,
	WALL6,
	WALL7,
	WALL8,
	WALL9,
	WALL10,
	WALL11,
	WALL12,
	WALL13,
	TOTAL
};

const int TILE_PER_ROW_IMAGE = 5;
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

#include "SDLWrapper.h"

/**
* Class that represents a tile.
* @todo Actually implement the tiles that will be in the game.
* @todo Implement solid tile.
*/
class Tile {

	public:
		/**
		* The constructor
		* Initializes all attributes.
		* @param x_ : The x for the tile rectangle.
		* @param y_ : The y for the tile rectangle.
		* @param tileType_ : The type of the tile.
		*/
		Tile(const int x_, const int y_, const int tileType_);

		/**
		* The destructor.
		*/
		~Tile();

		/**
		* @return The Tile rectangle (clip).
		*/
		SDL_Rect& getRectangle();

		/**
		* @return The Tile type.
		*/
		int getType();

	private:
		int type; /**< The type of the Tile. */
		SDL_Rect rectangle; /**< The clip for the Tile. */


};

#endif // INCLUDE_TILE_H

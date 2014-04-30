#ifndef INCLUDE_TILE_H
#define INCLUDE_TILE_H

enum TileCode : int {
	BLACK = 0,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	LIGHTBLUE,
	PINK,
	DARKGRAY,
	GRAY,
	TOTAL
};

const int TILE_PER_ROW_IMAGE = 5;
const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;

#include "SDLWrapper.h"

class Tile {

	public:
		Tile(int x_, int y_, int tileType_);
		~Tile();
		SDL_Rect& getRectangle();
		int getType();

		/// @todo Implement solid tile.
		int x;
		int y;

	private:
		int type;
		SDL_Rect rectangle;


};
#endif // INCLUDE_TILE_H

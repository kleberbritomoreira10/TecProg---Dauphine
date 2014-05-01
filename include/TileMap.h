#ifndef INCLUDE_TILEMAP_H
#define INCLUDE_TILEMAP_H

#define TILE_SIZE 48.0

#include "Entity.h"
#include "Tile.h"

#include <vector>

class TileMap : public Entity {

	public:

		TileMap(const std::vector<int>& tileData_);
		~TileMap();

		/**
		* Updates the entity.
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the
		* 	entity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		void create(const std::vector<int>& tileData_);

		std::vector<Tile*> tiles;

	private:
		void clipTiles();
		SDL_Rect clips[TileCode::TOTAL];


};

#endif // INCLUDE_TILEMAP_H
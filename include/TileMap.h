#ifndef INCLUDE_TILEMAP_H
#define INCLUDE_TILEMAP_H

#include "Entity.h"
#include "Tile.h"

#include <vector>

/**
* Represents the tile distrubution for a level.
* @todo Revise Tile placement implementation.
*/
class TileMap : public Entity {

	public:
		/**
		* The constructor.
		* @param tileData_ : The vector containing numerical value of the map.
		* @param path_ : Path to the desired tilesheet.
		* @see TileMap::create
		*/
		TileMap(const std::vector<int>& tileData_, const std::string& path_);

		/**
		* The destructor.
		* Deletes all the Tiles.
		*/
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

		std::vector<Tile*> tiles; /**< All the generated tiles. */

	private:
		/**
		* Creates the Tiles based on the numerical vector.
		* @param tileData_ : The vector containing numerical value of the map.
		*/
		void create(const std::vector<int>& tileData_);

		/**
		* Clips the tiles.
		* @todo Refactor this method.
		*/
		void clipTiles();

		SDL_Rect clips[TileCode::TOTAL]; /**< Contains all the clips for each tile. */
		

};

#endif // INCLUDE_TILEMAP_H
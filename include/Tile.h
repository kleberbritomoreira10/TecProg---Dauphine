#ifndef INCLUDE_TILE_H
#define INCLUDE_TILE_H

#include "Entity.h"
#include "Sprite.h"
#include "Camera.h"

class Tile : public Entity {

	public:

		Tile(double x_, double y_, Sprite* sprite_);
		virtual ~Tile();
		virtual void update(double dt_);
		virtual void render(const double cameraX_, const double cameraY_);
		bool isSolid();

	private:
		bool solid;

};

#endif // INCLUDE_TILE_H

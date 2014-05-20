#ifndef INCLUDE_CROSSHAIR_H
#define INCLUDE_CROSSHAIR_H

#include "Entity.h"

class Crosshair : public Entity{
	public:
		Crosshair(const double x_, const double y_, Sprite* const sprite_);
		~Crosshair();
		void update(const double dt_);
		void render(const double cameraX_, const double cameraY_);
		unsigned int getWidth();
		unsigned int getHeight();
		bool activated;
	private:


};

#endif // INCLUDE_CROSSHAIR_H
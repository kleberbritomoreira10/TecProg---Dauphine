#ifndef INCLUDE_TRAP_H
#define INCLUDE_TRAP_H

#include "DynamicEntity.h"

/**
* Class for the bomb potion.
*/
class Trap : public DynamicEntity {
	public:
		/**
		* The constructor.
		*/
		Trap(const double x_, const double y_, const std::string& path_);

		/**
		* The destructor.
		*/
		virtual ~Trap();

		/**
		*
		*/
		virtual void update(const double dt_);

		/**
		*
		*
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		bool activated;

	private:

		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){}
		virtual void updateBoundingBox(){}
};

#endif // INCLUDE_TRAP_H

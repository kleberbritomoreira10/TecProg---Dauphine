#ifndef INCLUDE_POTION_H
#define INCLUDE_POTION_H

#include "DynamicEntity.h"
#include "Player.h"

/**
* Class for the bomb potion.
* @todo Refactor so its a DynamicEntity.
*/

class Player;

class Potion : public DynamicEntity{
	public:
		/**
		*
		*
		*/
		Potion(const double x_, const double y_, Sprite* const sprite_);

		/**
		*
		*
		*/
		virtual ~Potion();

		/**
		*
		*
		*/
		virtual void update(const double dt_);

		/**
		*
		*
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		Sprite* getSprite();

		bool activated;
		int strength;
		int distance;
		double flightTime;

	private:

		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
};

#endif // INCLUDE_BOMBPOTION_H

#ifndef INCLUDE_BOMBPOTION_H
#define INCLUDE_BOMBPOTION_H

#include "Entity.h"

/**
* Class for the bomb potion.
* @todo Refactor so its a DynamicEntity.
*/
class BombPotion : public Entity{
	public:
		/**
		*
		*
		*/
		BombPotion(const double x_, const double y_, Sprite* const sprite_);

		/**
		*
		*
		*/
		virtual ~BombPotion();

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

		bool activated;
		bool isRight;
		int strength;
		double vx;
		double vy;
		int distance;


};

#endif // INCLUDE_BOMBPOTION_H

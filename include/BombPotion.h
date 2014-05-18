#ifndef INCLUDE_BOMBPOTION_H
#define INCLUDE_BOMBPOTION_H

#include "Entity.h"

class BombPotion : public Entity{
	public:
		BombPotion(const double x_, const double y_, Sprite* const sprite_);
		~BombPotion();
		void update(const double dt_);
		void render(const double cameraX_, const double cameraY_);

		bool activated;
		bool isRight;
		int strength;
		double vy;
		int distance;
	private:


};

#endif // INCLUDE_BOMBPOTION_H
#ifndef INCLUDE_DYNAMICENTITY_H
#define INCLUDE_DYNAMICENTITY_H

#include "Entity.h"

class DynamicEntity : public Entity {

	public:
		DynamicEntity(double x_, double y_, Sprite* sprite_);
		virtual ~DynamicEntity();

		/**
		* Updates the players position.
		* Update is based on what input was recieved, and the players velocity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void updatePosition(double dt_);

		double vx; /**< The player's speed on the x axis. */
		double vy; /**< The player's speed on the x axis. */
		double speed; /**< Speed that moves player on input. */
		double maxSpeed; /**< Player max speed. */
		bool isGrounded;

		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */

		virtual void jump();
		virtual void applyGravity();
		virtual void move(bool movingLeft_, bool movingRight_);
		virtual void slowVx();
		virtual void roll();

};

#endif // INCLUDE_DYNAMICENTITY_H
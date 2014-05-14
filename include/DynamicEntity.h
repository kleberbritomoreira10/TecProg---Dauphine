#ifndef INCLUDE_DYNAMICENTITY_H
#define INCLUDE_DYNAMICENTITY_H

#include "Entity.h"
#include "Tile.h"

#include <vector>

/**
* Subclass of Entity.
* The objects of this class are entities, but have physics applied to them (such as velocity).
*/
class DynamicEntity : public Entity {

	public:
		/**
		* The constructor.
		* Initializes all attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		DynamicEntity(const double x_, const double y_, Sprite* const sprite_);

		/**
		* The destructor.
		*/
		virtual ~DynamicEntity();


		virtual void jump();
		virtual void applyGravity();
		virtual void move(const bool movingLeft_, const bool movingRight_);
		virtual void slowVx();
		virtual void roll();

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		virtual void setLevelWH(const unsigned int width_, const unsigned int height_);

		virtual void setTiles(const std::vector<Tile*>& tiles_);

		double vx; /**< The dynamic entity's speed on the x axis. */
		double vy; /**< The dynamic entity's speed on the x axis. */
		double speed; /**< Speed that moves dynamic entity on input. */
		double maxSpeed; /**< Dynamic entity max speed. */		
		bool isGrounded; /**< Check for if the dynamic entity is on the ground. */

	protected:
		/**
		* Updates the position of the dynamic entity
		* Update is based on what input was recieved, and the players velocity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void updatePosition(const double dt_);

		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		std::vector<Tile*> tiles;

};

#endif // INCLUDE_DYNAMICENTITY_H
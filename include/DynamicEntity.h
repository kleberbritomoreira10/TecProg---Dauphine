#ifndef INCLUDE_DYNAMICENTITY_H
#define INCLUDE_DYNAMICENTITY_H

#include "Entity.h"
#include "Tile.h"

#include <vector>
using std::vector;

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
		DynamicEntity(double x_, double y_, Sprite* sprite_);

		/**
		* The destructor.
		*/
		virtual ~DynamicEntity();

		virtual void jump();
		virtual void applyGravity();
		virtual void move(bool movingLeft_, bool movingRight_);
		virtual void slowVx();
		virtual void roll();

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		virtual void setLevelWH(unsigned int width_, unsigned int height_);

		void setTiles(vector<Tile*>& tiles_);

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

		vector<Tile*> tiles;
		SDL_Rect rectangle;

};

#endif // INCLUDE_DYNAMICENTITY_H
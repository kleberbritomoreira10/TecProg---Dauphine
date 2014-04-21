#ifndef INCLUDE_ENTITY_H
#define INCLUDE_ENTITY_H

#include "Sprite.h"

/**
* Base class for all game objects (entities).
* The entity contains the (x,y) position, width and height, and a sprite.
*/
class Entity {

	public:
		/**
		* The destructor.
		* Deletes the sprite.
		*/
		virtual ~Entity();

		/**
		* Updates the entity.
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the
		* 	entity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_) = 0;

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		*/
		virtual void render() = 0;

		/**
		* @return The Entity width.
		*/
		unsigned int getWidth();

		/**
		* @return The Entity height.
		*/
		unsigned int getHeight();

		double x; /**< The position in the x axis. */
		double y; /**< The position in the y axis. */

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Entity(double x_, double y_, Sprite* sprite_);

		Sprite* sprite; /**< The Sprite attributed to the entity. */
		unsigned int width; /**< The entitys width, from its sprite. */
		unsigned int height; /**< The entitys height, from its sprite. */

};

#endif //INCLUDE_ENTITY_H

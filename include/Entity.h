#ifndef INCLUDE_ENTITY_H
#define INCLUDE_ENTITY_H

#include "Sprite.h"

/**
* Abstract base class for all the entities.
* Generic parent class for all the game's entities.
*/
class Entity {

	public:
		/**
		* The destructor.
		* Resets attributes and deletes the sprite.
		*/
		virtual ~Entity();

		/**
		* Updates the entity.
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the entity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_) = 0;

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		*/
		virtual void render() = 0;

		double x; /**< The position in the x axis. */
		double y; /**< The position in the y axis. */

	protected:
		Sprite *sprite; /**< The Sprite attributed to the entity. */

};

#endif //INCLUDE_ENTITY_H

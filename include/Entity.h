#ifndef INCLUDE_ENTITY_H
#define INCLUDE_ENTITY_H

#include "Sprite.h"

/**
* Class for all the entities.
* Generic parent class for all the game's entities.
*/
class Entity {

	public:
		/**
		* Updates the entity.
		* Updates whatever is necessary, relative to the entity.
		* @param dt : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt) const;

		/**
		* Renders the entity.
		* Copies the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		*/
		virtual void render() const;

		double x; /**< The position in the x axis. */
		double y; /**< The position in the y axis. */

	protected:
		Sprite *sprite; /**< The Sprite attributed to the entity. */

};

#endif //INCLUDE_ENTITY_H

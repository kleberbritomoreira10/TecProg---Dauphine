#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H

#include "Entity.h"

#include <list>

/**
* Parent class for other game states.
*/
class StateGame {

	public:
		/**
		* The destructor.
		* 
		*/
		virtual ~StateGame();

		/**
		* Loads necessary objects.
		* Pure virtual function. Purpose is to load all things relevant to the state.
		*/
		virtual void load() = 0;

		/**
		* Update all entities.
		* Pure virtual function. Purpose is to update all the entities in the list.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_) = 0;

		/**
		* Unloads necessary objects.
		* Pure virtual function. Purpose is to unload whatever was previously loaded.
		*/
		virtual void unload() = 0;

		/**
		* Renders the level.
		* Always render on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render() = 0;

		/**
		* Adds an entity to the list.
		*/
		void addEntity(Entity* entity);

		/**
		* Deletes all the entities inside the list, and clears it.
		*/
		void cleanEntities();

	protected:
		std::list<Entity*> entities; /**< List of all the entities in the state. */

};

#endif //INCLUDE_STATE_H

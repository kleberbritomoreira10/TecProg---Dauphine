#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H

#include "Entity.h"

#include <list>
using std::list;

class State {

	public:
		/**
		* The destructor.
		* 
		*/
		virtual ~State();

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

		list<Entity*> entities; /**< List of all the entities in the state. */

};

#endif //INCLUDE_STATE_H

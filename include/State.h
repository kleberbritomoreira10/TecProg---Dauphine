#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H

#include "Entity.h"

#include <list>
using std::list;

class State {

	public:

		/**
		*
		*/
		virtual ~State();

		/**
		*
		*/
		virtual void load() = 0;

		/**
		*
		*/
		virtual void update(double dt_) = 0;

		/**
		*
		*/
		virtual void unload() = 0;

		/**
		*
		*/
		void addEntity(Entity *entity);

	protected:

		list<Entity*> entities; /**< List of all the entities in the state. */

};

#endif //INCLUDE_STATE_H

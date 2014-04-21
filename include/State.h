#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H

#include "Entity.h"
#include "Player.h"

#include <list>
using std::list;

#include <cstdint>

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
		* Renders the level.
		* Always render on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render() = 0;

		/**
		*
		*/
		void addEntity(Entity *entity);

		virtual Player* getPlayer();

	protected:

		list<Entity*> entities; /**< List of all the entities in the state. */

};

#endif //INCLUDE_STATE_H

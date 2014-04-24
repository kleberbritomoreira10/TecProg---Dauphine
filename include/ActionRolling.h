#ifndef INCLUDE_ACTIONROLLING_H
#define INCLUDE_ACTIONROLLING_H

#include "Action.h"

class ActionRolling : public Action {

	public:

		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		ActionRolling();

		/**
		* The destructor.
		*/
		~ActionRolling();

		/**
		* Loads the entity.
		* Loads all the necessary parameters from the entity.
		*/
		virtual void load();

		/**
		* Updates the objects within the Action.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see ActionRolling::load
		*/
		virtual void unload();

		/**
		* Renders the action's sprite.
		* @see Sprite::render
		*/
		virtual void render();

		virtual void setPlayer(Player* player_);

		Player* getPlayer();

};

#endif // INCLUDE_ACTIONROLLING_H

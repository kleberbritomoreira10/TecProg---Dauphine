#ifndef INCLUDE_ACTIONIDLE_H
#define INCLUDE_ACTIONIDLE_H

#include "Action.h"

class ActionIdle : public Action {

	public:

		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		ActionIdle();

		/**
		* The destructor.
		*/
		~ActionIdle();

		/**
		* Loads the player.
		* Loads all the necessary parameters from the player.
		*/
		virtual void load();

		/**
		* Updates the objects within the Action.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see ActionIdle::load
		*/
		virtual void unload();

		/**
		* Renders the action's sprite.
		* @see Sprite::render
		*/
		virtual void render();

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player* player_);

};

#endif // INCLUDE_ACTIONIDLE_H

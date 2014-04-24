#ifndef INCLUDE_ACTIONAERIAL_H
#define INCLUDE_ACTIONAERIAL_H

#include "Action.h"

class ActionAerial : public Action {

	public:

		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		ActionAerial();

		/**
		* The destructor.
		*/
		~ActionAerial();

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
		* @see ActionAerial::load
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

#endif // INCLUDE_ACTIONAERIAL_H

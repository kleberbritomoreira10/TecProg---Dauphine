#ifndef INCLUDE_ACTIONMOVING_H
#define INCLUDE_ACTIONMOVING_H

#include "Action.h"

class ActionMoving : public Action {

	public:

		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		ActionMoving();

		/**
		* The destructor.
		*/
		~ActionMoving();

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
		* @see ActionMoving::load
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

#endif // INCLUDE_ACTIONMOVING_H
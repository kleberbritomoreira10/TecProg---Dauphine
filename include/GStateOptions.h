#ifndef INCLUDE_GSTATEOPTIONS_H
#define INCLUDE_GSTATEOPTIONS_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial menu screen.
* Game state that will contain the game over screen.
*/
class GStateOptions : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStateOptions();

		/**
		* The destructor.
		*/
		virtual ~GStateOptions();

		/**
		* Loads the level.
		* From the menu.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Unloads everything that was loaded.
		* @see GStateOptions::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		Sprite* optionsImage; /**< The image shown on the menu. */

};

#endif // INCLUDE_GSTATEOPTIONS_H

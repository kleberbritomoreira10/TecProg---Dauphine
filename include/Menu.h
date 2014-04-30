#ifndef INCLUDE_STATEmenu_H
#define INCLUDE_STATEmenu_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial menu screen.
* Game state that will contain the initial menu images, before the main menu state is called.
*/
class Menu : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		Menu();

		/**
		* The destructor.
		*/
		virtual ~Menu();

		/**
		* Loads the level.
		* From the menu.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see Menu::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		
		Sprite* menu; /**< The image shown on the menu. */
		double passedTime; /**< The time already elapsed since the beggining of the menu. */
		double lifeTime; /**< The amount of time the menu will be shown. */

};

#endif // INCLUDE_STATEmenu_H
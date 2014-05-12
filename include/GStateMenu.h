#ifndef INCLUDE_GSTATEMENU_H
#define INCLUDE_GSTATEMENU_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial menu screen.
* Game state that will contain the main menu.
*/
class GStateMenu : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStateMenu();

		/**
		* The destructor.
		*/
		virtual ~GStateMenu();

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
		* @see GStateMenu::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

		void handleSelectorMenu();

	private:
		Sprite* menuImage; /**< The image shown on the menu. */
		Sprite* menuSelector; /**< The selector shown on the menu. */
		double passedTime; /**< The time already elapsed since the beggining of the menu. */
		double lifeTime; /**< The amount of time the menu will be shown. */
		int selectorXPositionLeft[4]; /**< The X position of the left selector.. */
		int selectorYPositionLeft[4]; /**< The Y position of the left selector.. */
		int selectorXPositionRight[4]; /**< The X position of the left selector.. */
		int selectorYPositionRight[4]; /**< The Y position of the left selector.. */
		int selectorPosition;
};

#endif // INCLUDE_GSTATEMENU_H
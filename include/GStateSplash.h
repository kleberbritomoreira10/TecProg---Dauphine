#ifndef INCLUDE_STATESPLASH_H
#define INCLUDE_STATESPLASH_H

#include "StateGame.h"
#include "Sprite.h"

#define NUMBER_OF_SPLASH_IMAGES 4

/**
* The state for the initial splash screen.
* Game state that will contain the initial splash images, before the main menu state is called.
*/
class GStateSplash : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStateSplash();

		/**
		* The destructor.
		*/
		virtual ~GStateSplash();

		/**
		* Loads the level.
		* From the Splash.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see GStateSplash::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		int current;
		double passedTime; /**< The time already elapsed since the beggining of the splash. */
		double lifeTime; /**< The amount of time the splash will be shown. */
		Sprite* images[NUMBER_OF_SPLASH_IMAGES];

};

#endif // INCLUDE_STATESPLASH_H
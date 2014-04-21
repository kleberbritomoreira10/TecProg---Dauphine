#ifndef INCLUDE_STATESPLASH_H
#define INCLUDE_STATESPLASH_H

#include "State.h"
#include "Sprite.h"

class StateSplash : public State {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		StateSplash();

		/**
		* The destructor.
		*/
		~StateSplash();

		/**
		* Loads the level.
		* From the Splash.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the State.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see StateSplash::load()
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render();

	private:
		
		Sprite* splash; /**< The image shown on the splash. */
		double passedTime; /**< The time already elapsed since the beggining of the splash. */
		double lifeTime; /**< The amount of time the splash will be shown. */

};

#endif // INCLUDE_STATESPLASH_H
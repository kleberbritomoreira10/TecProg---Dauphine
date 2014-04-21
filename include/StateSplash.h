#ifndef INCLUDE_STATESPLASH_H
#define INCLUDE_STATESPLASH_H

#include "State.h"
#include "Sprite.h"

class StateSplash : public State {

	public:

		StateSplash();

		~StateSplash();

		/**
		*
		*/
		virtual void load();

		/**
		*
		*/
		virtual void update(double dt_);

		/**
		*
		*/
		virtual void unload();

		/**
		* Renders the level.
		* Always render on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render();

	private:
		Sprite *splash;
		double passedTime;
		double lifeTime;


};

#endif // INCLUDE_STATESPLASH_H
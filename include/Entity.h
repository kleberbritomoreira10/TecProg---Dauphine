#ifndef INCLUDE_ENTITY_H
#define INCLUDE_ENTITY_H

#include "SDLWrapper.h"
#include "Sprite.h"

class Entity {

	public:
		/**
		* Updates entity.
		* Modifies whatever is necessary, relative to the entity.
		* @params dt : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt) const;

		/**
		* Renders entity.
		* Copies the entity onto the desired renderer.
		*/
		virtual void render() const;

		double x;
		double y;

	protected:
		Sprite *sprite;
		SDL_Renderer *renderer;

};

#endif //INCLUDE_ENTITY_H

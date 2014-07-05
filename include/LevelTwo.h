#ifndef INCLUDE_LEVELTWO_H
#define INCLUDE_LEVELTWO_H

#include "Level.h"
#include "Sprite.h"

/**
* The first level of the game.
* Derived from Level class.
*/
class LevelTwo : public Level {
	
	public:
		/**
		* The constructor.
		* @see Level::Level()
		*/
		LevelTwo();

		/**
		* The destructor.
		*/
		virtual ~LevelTwo();

		/**
		* Loads the level.
		* From the Level1.lua script, loads all the necessary objects.
		*/
		virtual void load();
		
		/**
		* Updates the objects within the Level.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Unloads everything that was loaded.
		* @see LevelTwo::load()
		*/
		virtual void unload();

		/**
		* Renders the level.
		* Always renders on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render();

		int itens[4];
		bool pego[4];
		int unsigned numeroItens = 4;

};

#endif //INCLUDE_LEVELTWO_H

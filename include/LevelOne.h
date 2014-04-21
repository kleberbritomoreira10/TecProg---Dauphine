#ifndef INCLUDE_LEVELONE_H
#define INCLUDE_LEVELONE_H

#include "Level.h"

/**
* The first level of the game.
* Derived from Level class.
*/
class LevelOne : public Level {
	
	public:
		/**
		* The constructor.
		* @see Level::Level()
		*/
		LevelOne();

		/**
		* The destructor.
		*/
		virtual ~LevelOne();

		/**
		* Loads the level.
		* From the Level1.lua script, loads all the necessary objects.
		*/
		virtual void load();
		
		/**
		* Updates the objects within the Level.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(double dt_);

		/**
		* Unloads everything that was loaded.
		* @see LevelOne::load()
		*/
		virtual void unload();

		/**
		* Renders the level.
		* Always renders on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render();

	protected:
		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player* player_);

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		virtual void setCamera(Camera* camera_);

};

#endif //INCLUDE_LEVELONE_H

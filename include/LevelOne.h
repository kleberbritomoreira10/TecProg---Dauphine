#ifndef INCLUDE_LEVELONE_H
#define INCLUDE_LEVELONE_H

#include "State.h"
#include "Level.h"

/**
* The first level of the game.
* 
*/
class LevelOne : public Level {
	
	public:
		/**
		* The constructor.
		* 
		*/
		LevelOne();

		/**
		* The destructor.
		* 
		*/
		virtual ~LevelOne();

		/**
		*
		*/
		virtual void load();
		
		/**
		* Updates the objects within the Level.
		* Calls 
		* @note Sets the relevant information for its Player and Camera.
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

	protected:

		/**
		* @param player_ : Sets the player for the level.
		*/
		virtual void setPlayer(Player *player_);

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		virtual void setCamera(Camera *camera_);

};

#endif //INCLUDE_LEVELONE_H

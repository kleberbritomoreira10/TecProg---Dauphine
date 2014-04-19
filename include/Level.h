#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "Sprite.h"
#include "SDLWrapper.h"
#include "Player.h"
#include "Camera.h"
#include "Entity.h"
#include "State.h"

#include <list>
using std::list;

/**
* Represents the current level.
* Contains background, player and a camera. Should contain all(?) game objects related to that level in the future.
*/
class Level : public State {
	
	public:
		/**
		* The constructor.
		* Defines the levels width and height limits.
		* @param background_ : Sets the background sprite, which defines the levels width and height.
		* @todo Probably isn't the best practice to make the background define the width/height. We might not want a background sprite later.
		*/
		Level(Sprite *background_);

		/**
		* The destructor.
		* Resets all attributes.
		*/
		~Level();

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
		* @param clip_ : Clips the texture, on the SDL_Rect bounds.
		* @see Sprite::render()
		*/
		void render(SDL_Rect &clip_);

		/**
		* @return The Level width.
		*/
		unsigned int getWidth();

		/**
		* @return The Level height.
		*/
		unsigned int getHeight();

		/**
		* @param player_ : Sets the player for the level.
		*/
		void setPlayer(Player &player_);

		/**
		* @param camera_ : Sets the camera for the level.
		* @note You should only set the camera after setting the player. Will warn if you didn't.
		*/
		void setCamera(Camera &camera_);

		/**
		*
		*/
		void addEntity(Entity *entity);

	private:
		Sprite *background; /**< The levels background sprite. */

		unsigned int width; /**< Width that defines the horizontal limits. */
		unsigned int height; /**< Height that defines the vertical limits. */

		Player *player; /**< The direct reference to player, even though its in the list. */
		Camera *camera; /**< The current camera for that Level. */

		list<Entity*> entities; /**< List of all the entities in the level. */

};

#endif //INCLUDE_LEVEL_H

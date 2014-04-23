#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Entity.h"
#include "Sprite.h"
#include "InputKeys.h"

#include <array>
using std::array;

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public Entity {

	public:
		/**
		* Possible player states.
		*/
		enum State : int {
			STATE_STANDING = 0,
			STATE_WALKING,
			STATE_JUMPING,
			STATE_CROUCHING,
			STATE_ROLLING
		};

		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Player(double x_, double y_, Sprite* sprite_);

		/**
		* The destructor.
		* Deletes the sprite.
		* @todo See if just the entity deleting the sprite is enough.
		*/
		virtual ~Player();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(double dt_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render()
		*/
		virtual void render();

		/**
		* Updates the players position.
		* Update is based on what input was recieved, and the players velocity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		void updatePosition(double dt_);

		/**
		* Updates the player depending on recieved input.
		* Modifies whatever is necessary, relative to the player.
		*/
		void updateInput();

		/**
		* @param x_, y_ : Tells the player what are the current (x,y) position of the camera.
		* @see Level::update()
		*/
		void setCameraXY(double x_, double y_);

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(unsigned int width_, unsigned int height_);

		State state; /**< Current state the player is in (for the player internal state). */

	private:
		double vx; /**< The player's speed on the x axis. */
		double vy; /**< The player's speed on the x axis. */
		double speed; /**< Speed that moves player on input. */
		double maxSpeed; /**< Player max speed. */

		double cameraX; /**< The current x position of the camera. */
		double cameraY; /**< The current y position of the camera. */
		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		
};

#endif //INCLUDE_PLAYER_H

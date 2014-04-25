#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "Entity.h"
#include "Sprite.h"
#include "InputKeys.h"
#include "Action.h"

class Action;

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public Entity {

	public:
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
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		/**
		* Updates the players position.
		* Update is based on what input was recieved, and the players velocity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		void updatePosition(double dt_);

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(unsigned int width_, unsigned int height_);

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		static void initializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		static void destroyStates();

		/**
		* Sets the current game state.
		* @see Action::load
		* @see Action::unload
		* @param state_ : The state you want to be changed into. All states are inside Player.
		*/
		static void setAction(Action& action_);

		static Action* actionIdle; /**< The action of stand. First state of the player. */
		static Action* actionAerial; /**< The action of */
		static Action* actionMoving; /**< The action of */
		static Action* actionRolling; /**< The action of */
		static Action* actionCrouching; /**< The action of */

		double vx; /**< The player's speed on the x axis. */
		double vy; /**< The player's speed on the x axis. */
		double speed; /**< Speed that moves player on input. */
		double maxSpeed; /**< Player max speed. */
		bool isGrounded;

		void jump();
		void applyGravity();
		void move(bool movingLeft_, bool movingRight_);
		void slowVx();
		void roll();

	private:
		
		static Action* currentAction; /**< The current action, which the player is in. */

		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		
};

#endif //INCLUDE_PLAYER_H

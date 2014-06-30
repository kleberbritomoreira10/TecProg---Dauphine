#ifndef INCLUDE_BOSS_H
#define INCLUDE_BOSS_H

#include "DynamicEntity.h"
#include "StateBoss.h"
#include "Animation.h"
#include "Potion.h"
#include <map>
#include <vector>

class StateBoss;

class Boss : public DynamicEntity {

	public:

		enum BStates : uint8_t {
			IDLE = 0,
			ATTACK,
			DEAD
		};

		/**
		* The constructor.
		*/
		Boss(const double x_, const double y_, const std::string& path_);

		/**
		* The destructor.
		*/
		virtual ~Boss();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(const double dt_);

		void initializeStates();
		void destroyStates();
		void changeState(const BStates state_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		void usePotion(const int strength_, const int distance_);
		
		unsigned int potionsLeft;
		Animation* getAnimation();
		bool isDead();
		void setDead(bool isDead_);

		bool sawPlayer;
		std::vector<Potion*> potions;

	private:
		virtual void updateBoundingBox();
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		StateBoss* currentState;
		Animation* animation;
		std::map<BStates, StateBoss*> statesMap;
		bool dead;

};

#endif // INCLUDE_BOSS_H

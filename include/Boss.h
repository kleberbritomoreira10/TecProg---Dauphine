#ifndef INCLUDE_BOSS_H
#define INCLUDE_BOSS_H

#include "DynamicEntity.h"
#include "Animation.h"

class Boss : public DynamicEntity {

	public:

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

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);
		
		Animation* getAnimation();
		bool isDead();
		void setDead(bool isDead_);

	private:
		virtual void updateBoundingBox();
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		Animation* animation;
		bool dead;

};

#endif // INCLUDE_BOSS_H

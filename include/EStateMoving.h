#ifndef INCLUDE_ESTATEMOVING_H
#define INCLUDE_ESTATEMOVING_H

#include "StateEnemy.h"

class EStateMoving : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateMoving(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateMoving(){}

		/**
		* @see StateEnemy::enter
		*/
		virtual void enter();

		/**
		* @see StateEnemy::exit
		*/
		virtual void exit();

		/**
		* @see StateEnemy::update
		*/
		virtual void update();

};

#endif // INCLUDE_ESTATEMOVING_H

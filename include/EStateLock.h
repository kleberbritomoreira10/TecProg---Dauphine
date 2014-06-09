#ifndef INCLUDE_ESTATELOCK_H
#define INCLUDE_ESTATELOCK_H

#include "StateEnemy.h"

class EStateLock : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateLock(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateLock(){}

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
		virtual void update(const double dt_);

};

#endif // INCLUDE_ESTATELOCK_H

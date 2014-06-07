#ifndef INCLUDE_ESTATEATACK_H
#define INCLUDE_ESTATEATACK_H

#include "StateEnemy.h"

class EStateAtack : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateAtack(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateAtack(){}

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

#endif // INCLUDE_ESTATEATACK_H

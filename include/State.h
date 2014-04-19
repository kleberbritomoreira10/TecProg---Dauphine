#ifndef INCLUDE_STATE_H
#define INCLUDE_STATE_H

#include <cstdint>

class State {

	public:

		// enum class GameState : uint8_t {
		//     Menu, Level_One, Quit
		// };

		/**
		*
		*/
		virtual ~State();

		/**
		*
		*/
		virtual void load() = 0;

		/**
		*
		*/
		virtual void update(double dt_) = 0;

		/**
		*
		*/
		virtual void unload() = 0;

};

#endif //INCLUDE_STATE_H

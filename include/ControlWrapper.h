#ifndef INCLUDE_CONTROLWRAPPER_H
#define INCLUDE_CONTROLWRAPPER_H

// #include "SDLWrapper.h"
// #include <cmath>

// #define CONTROLLERSTICK_DEAD_ZONE 8000;
// #define SHOULDER_DEAD_ZONE 8000;

// #define CONTROL_EVENT

// namespace commands{

// 	enum{
		
// 		UP,
// 		DOWN,
// 		LEFT,
// 		RIGHT,

// 		JUMP,
// 		ATTACK,
// 		USE,
// 		HOOK,

// 		ROLL,
// 		AIM,
// 		CROUCH,
// 		INVENTORY,

// 		START,
// 		SELECT
// 	};

// }

/**
* @todo Refactor.
*/
class ControlWrapper {
	
// 	public:
// 		/**
// 		* Pointers to the game controller and keyboard
// 		*/
// 		Uint32 controlEventType;

// 		*
// 		* Initializes Controller managing.
// 		* Initializes the Control manager, sets the SDL User Event. 
// 		* If no controller is found, defaults to keyboard
		
// 		static void initialize();

// 		/**
// 		* Checks the input and decides the appropriate SDL_UserEvent data fields, then pushes this event to the stack.  
// 		*/
// 		static void decide();
	
// 	private:
// 		/**
// 		* Pointer to the game controller and keyboard
// 		*/
// 		static SDL_GameController* gameController;
};

#endif // INCLUDE_CONTROLWRAPPER_H
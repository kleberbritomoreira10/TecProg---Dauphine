#ifndef INCLUDE_CONTROLWRAPPER_H
#define INCLUDE_CONTROLWRAPPER_H
#include "SDLWrapper.h"
#include "Logger.h"
#include <cmath>

#define CONTROLLERSTICK_DEAD_ZONE 8000;
#define TRIGGER_DEAD_ZONE 8000;

#define CONTROL_EVENT

namespace commands{

	/**
	* Command Enumeration to be used on the data field for the user event to be pushed on the stack after control evaluation
	* 
	*/

	enum{		
 		UP,
		DOWN,
		LEFT,
		RIGHT,

		JUMP,
		ATTACK,
		USE,
		HOOK,

		ROLL,
		AIM,
		CROUCH,
		INVENTORY,

		START,
		SELECT
	};
}

namespace controller{

	/**
	* Button Enumeration for the Joystick
	*/

	enum buttons{		
 		FACE_DOWN, //X on PS4 controller - 0
 		FACE_RIGHT, //O on PS4 controller - 1
 		FACE_LEFT, //[] on PS4 controller - 2
 		FACE_UP, ///\ on PS4 controller - 3
 		
 		SELECT, //SHARE on PS4 controller - 4
 		HOME, // PS Button on PS4 controller - 5
 		START, //OPTIONS on PS4 controller - 6
 		
 		L3, //Left analogue button - 7
 		R3, //Right analogue button  - 8
 		
 		LDTRIGGER, //Left Digital Trigger - 9
 		RDTRIGGER, //Right Digital Trigger  - 10
 		 
 		DUP, //D-Pad up - 11
 		DDOWN, //D-Pad down - 12
 		DLEFT, //D-Pad left - 13
 		DRIGHT, //D-Pad rigth - 14

 		PRESSED,
 		RELEASED
	};

	enum axes{
		LHORIZONTAL, //Left Analogue Stick X - 0
		LVERTICAL, //Left Analogue Stick Y - 1
		
		RHORIZONTAL, //Left Analogue Stick X - 2
		RVERTICAL, //Left Analogue Stick Y - 3

		LATRIGGER, //Left Analogue Trigger - 4
		RATRIGGER //Left Analogue Trigger Y - 5
	};
}
class ControlWrapper {
	
	public:
		/**
		* Singleton implementation.
		* @return The ControlWrapper::instance
		*/
		static ControlWrapper* getInstance();
		
		/**
		* Handles controller the input.
		* Detects the pending events, and simulates an appropriate KeyEvent by pushing one into a stack.
		*/
		static void decide();

	private:
		/**
		* The constructor.
		* Used to create the control wrapper instance.
		*/
		ControlWrapper();

		static ControlWrapper* instance; /**< The InputHandler instance (Singleton). */
		static SDL_GameController* gameController; /**< Pointer to the controller */
	// public:
	// 	static ControlWrapper* getInstance();

	// 	/**
	// 	* Checks the controller input and decides the appropriate SDL_KeyEvent fields, then pushes this event to the stack.  
	// 	*/
	// 	void decide();
	
	// private:
	// 	*
	// 	* Initializes Controller managing.
	// 	* Initializes the Control manager, sets the SDL User Event. 
	// 	* If no controller is found, defaults to keyboard
		
	// 	ControlWrapper();

	// 	SDL_GameController* gameController;

	// 	SDL_Event eventHandler; /** SDL internal event handler. */
};

#endif

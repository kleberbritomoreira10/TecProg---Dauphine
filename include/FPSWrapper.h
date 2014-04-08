#ifndef INCLUDE_FPSWRAPPER_H
#define INCLUDE_FPSWRAPPER_H

#include "SDLWrapper.h"

/**
* Wraps FPS handling in a class.
* Uses SDL2_GFX, by ferzkopp.
*/
class FPSWrapper {
	
	public:
		/**
		* Initializes FPS managing.
		* Initializes the FPS manager and sets it to the desired framerate (Configuration::MAX_FRAMERATE).
		* @param fpsManager_ : The FPS manager to handle.
		* @note Will warn if failed to set FPS.
		*/
		static void initialize(FPSmanager &fpsManager_);

		/**
		* Delays execution and calculates FPS.
		* Only if needed, delays the execution.
		* @param fpsManager_ : The FPS manager to handle.
		* @return The time in seconds since the last call.
		*/
		static double delay(FPSmanager &fpsManager_);
		
};

#endif //INCLUDE_FPSWRAPPER_H

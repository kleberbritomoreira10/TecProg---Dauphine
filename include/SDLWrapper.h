#ifndef INCLUDE_SDLWRAPPER_H
#define INCLUDE_SDLWRAPPER_H

// Add other SDL libraries here.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_framerate.h>

class SDLWrapper{
	public:
		/**
		* The system initializer.
		* Initializes all the SDL systems and/or subsystems.
		* @return true if every system was initialized successfully, else it returns false.
		*/
		static bool initialize();

		/**
		* Closes all open systems.
		* Closes all systems and/or subsystems opened by the initializer method.
		* @see initialize()
		*/
		static void close();
};

#endif // INCLUDE_SDLWRAPPER_H 

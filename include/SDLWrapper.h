#ifndef INCLUDE_SDLWRAPPER_H
#define INCLUDE_SDLWRAPPER_H

// Add other SDL libraries here.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDLWrapper{
	public:
		/* Initializes all the SDL systems. */
		static bool initialize();
		/* Closes the SDL systems. */
		static void close();
};

#endif // INCLUDE_SDLWRAPPER_H 

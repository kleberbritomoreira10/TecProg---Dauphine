#include "SDLWrapper.h"
#include "Logger.h"

bool SDLWrapper::initialize(){
	/// @todo Check if initializing each subsystem separately is worth it.

	bool initSDL = false;
	bool initIMG = false;

	// Initializing SDL with initFlags.
	const Uint32 initFlags = SDL_INIT_EVERYTHING;
	const int sdlInit = SDL_Init(initFlags);
	if(sdlInit == 0){
		initSDL = true;
	}
	else{
		Logger::errorSDL("Could not initialize SDL.", SDL_GetError());
	}

	// Initializing SDL_image with imgFlags.
	const Uint32 imgFlags = IMG_INIT_PNG;
	if((IMG_Init(imgFlags) & imgFlags)){
		initIMG = true;
	}
	else{
		Logger::errorSDL("Could not initialize SDL_IMG.", IMG_GetError());
	}

	// If even one system fails to initialize, returns false.
	return (initSDL && initIMG);
}

void SDLWrapper::close(){
	// Quits SDL_image.
	IMG_Quit();
	// Quits SDL.
	SDL_Quit();
}

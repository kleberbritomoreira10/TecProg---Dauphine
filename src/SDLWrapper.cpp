#include "SDLWrapper.h"
#include "Logger.h"

bool SDLWrapper::initialize(){
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

	// Initializing SDL_image with IMG_INIT_PNG.
	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		initIMG = true;
	}
	else{
		Logger::errorSDL("Could not initialize SDL_IMG.", IMG_GetError());
	}

	return (initSDL && initIMG);
}

void SDLWrapper::close(){
	IMG_Quit();
	SDL_Quit();
}

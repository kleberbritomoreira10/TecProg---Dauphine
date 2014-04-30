#include "SDLWrapper.h"
#include "AudioHandler.h"
#include "Logger.h"
#include "ControllerHandler.h"

bool SDLWrapper::initialize(){
	/// @todo Initialize SDL_Mixer and SDL_TTF. And not do INIT_EVERYTHING.

	bool initSDL = false;
	bool initIMG = false;
	bool initMixer = false;

	// Initializing SDL with initFlags.
	const Uint32 initFlags = SDL_INIT_EVERYTHING;
	const int sdlInit = SDL_Init(initFlags);
	if(sdlInit == 0){
		initSDL = true;
		Logger::verbose("Initialized SDL.");
	}
	else{
		Logger::errorSDL("Could not initialize SDL.", SDL_GetError());
	}

	// Initializing SDL_image with imgFlags.
	const Uint32 imgFlags = IMG_INIT_PNG;
	if((IMG_Init(imgFlags) & imgFlags)){
		initIMG = true;
		Logger::verbose("Initialized SDL_Image.");
	}
	else{
		Logger::errorSDL("Could not initialize SDL_Image.", IMG_GetError());
	}

	// Initializing SDL_mixer.
	AudioHandler* audioHandler = AudioHandler::getInstance();
	if(audioHandler != nullptr){
		initMixer = true;
		Logger::verbose("Initialized SDL_Mixer.");
	}
	else{
		Logger::errorSDL("Could not initialize SDL_Mixer", Mix_GetError());
	}

	/**
	*Initializes controller Wrapper. 
	*No need to check for failures as it will default back to keyboard in case it does not manage to initialize properly
	*/
	ControllerHandler* controlWrapper = ControllerHandler::getInstance();
	(void(controlWrapper));

	// If even one system fails to initialize, returns false.
	return (initSDL && initIMG && initMixer);
}

void SDLWrapper::close(){
	Logger::verbose("Closing SDL.");
	// Quits SDL_image.
	IMG_Quit();
	// Quits SDL.
	SDL_Quit();
}

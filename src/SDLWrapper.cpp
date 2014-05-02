#include "SDLWrapper.h"
#include "Logger.h"
#include <sstream>

bool SDLWrapper::initialize(){
	/// @todo Initialize SDL_Mixer and SDL_TTF. And not do INIT_EVERYTHING.

	bool initSDL = false;
	bool initIMG = false;
	bool initMixer = false;

	SDL_version compiled;

	// Initializing SDL with initFlags.
	const Uint32 initFlags = SDL_INIT_EVERYTHING;
	const int sdlInit = SDL_Init(initFlags);
	if(sdlInit == 0){
		initSDL = true;

		SDL_version linked;
		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);

		Logger::verbose("Initialized SDL.");
		SDLWrapper::logSDLVersion("SDL", compiled, linked, SDL_GetRevision());
	}
	else{
		Logger::errorSDL("Could not initialize SDL.", SDL_GetError());
	}

	// Initializing SDL_image with imgFlags.
	const Uint32 imgFlags = IMG_INIT_PNG;
	if((IMG_Init(imgFlags) & imgFlags)){
		initIMG = true;

		Logger::verbose("Initialized SDL_Image.");
		SDL_IMAGE_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_image", compiled, *IMG_Linked_Version());
	}
	else{
		Logger::errorSDL("Could not initialize SDL_Image.", IMG_GetError());
	}

	// Initializing SDL_mixer.
	const int frequency = 44100;
	const int channels = 2;
	const int chunksize = 4096;
	const int initialized = Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);
	if(initialized == 0){
		initMixer = true;

		Logger::verbose("Initialized SDL_Mixer.");
		SDL_MIXER_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_mixer", compiled, *Mix_Linked_Version());
	}
	else{
		Logger::errorSDL("Could not initialize SDL_Mixer", Mix_GetError());
	}

	// If even one system fails to initialize, returns false.
	return (initSDL && initIMG && initMixer);
}

void SDLWrapper::close(){
	Logger::verbose("Closing SDL.");

	// Quits SDL_mixer.
	Mix_CloseAudio();
	Mix_Quit();

	// Quits SDL_image.
	IMG_Quit();

	// Quits SDL.
	SDL_Quit();
}

void SDLWrapper::logSDLVersion(const std::string& what, const SDL_version& compiled,
	const SDL_version& linked, std::string revision){

	std::stringstream ss;

	ss << what << " Version (Compiled): " << (int)compiled.major << "." << (int)compiled.minor
		<< "." << (int)compiled.patch;

	if (!revision.empty()){
		ss << " (" << revision << ")";
	}
	
	Logger::verbose(ss.str());
	Logger::verbose(what + " Version (Runtime):  " + std::to_string(linked.major) + "." +
		std::to_string(linked.minor) + "." + std::to_string(linked.patch));
}

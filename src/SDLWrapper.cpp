#include "SDLWrapper.h"
#include "Logger.h"
#include <sstream>

bool SDLWrapper::initialize(){
	bool initSDL = false;
	bool initIMG = false;
	bool initMixer = false;
	bool initTTF = false;

	SDL_version compiled;

	const int ttfInit = TTF_Init();
	if(ttfInit == 0){
		initTTF = true;

		Logger::verbose("Initialized TTF");		
		SDL_TTF_VERSION(&compiled);
		SDLWrapper::logSDLVersion("SDL_TTF", compiled, *TTF_Linked_Version());
	}
	else{
		Logger::errorSDL("Could not initialize TTF.", TTF_GetError());
	}


	printf("SDL_ttf inicializada com sucesso!\n");

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
	return (initSDL && initIMG && initMixer && initTTF);
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

	TTF_Quit();

}

void SDLWrapper::logSDLVersion(const std::string& what_, const SDL_version& compiled_,
	const SDL_version& linked_, std::string revision_){

	std::stringstream ss;

	ss << what_ << " Version (Compiled): " << (int)compiled_.major << "." << (int)compiled_.minor
		<< "." << (int)compiled_.patch;

	if (!revision_.empty()){
		ss << " (" << revision_ << ")";
	}
	
	Logger::verbose(ss.str());
	Logger::verbose(what_ + " Version (Runtime):  " + std::to_string(linked_.major) + "." +
		std::to_string(linked_.minor) + "." + std::to_string(linked_.patch));
}

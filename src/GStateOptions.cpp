#include "GStateOptions.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateOptions::GStateOptions() :
	elapsedTime(0.0),
	optionsImage(nullptr),
	currentResolution(R_800_600),
	currentOption(O_RESOLUTION),
	selector(nullptr),
	selectorXPositionLeft  {780, 780, 780, 590, 590},
	selectorYPositionLeft  {365, 468, 580, 665, 750},
	selectorXPositionRight {1010, 1010, 1010, 900, 900},
	selectorYPositionRight {365, 468, 580, 665, 750}
{
	for(unsigned int i = 0; i < R_TOTAL; i++){
		this->resolutions[i] = nullptr;
	}
}

GStateOptions::~GStateOptions(){

}

void GStateOptions::update(const double dt_){
	this->elapsedTime += dt_;

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::DOWN] == true){
		if(this->elapsedTime >= selectorDelayTime){
			if(this->currentOption == (O_TOTAL - 1)){
				this->currentOption = O_RESOLUTION;
			}
			else{
				this->currentOption++;
			}
			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::UP] == true){
		if(this->elapsedTime >= selectorDelayTime){
			if(this->currentOption == O_RESOLUTION){
				this->currentOption = (O_TOTAL - 1);
			}
			else{
				this->currentOption--;
			}
			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::LEFT] == true){
		if(this->elapsedTime >= selectorDelayTime){
			// Option == Resolution
			if(this->currentOption == O_RESOLUTION){
				if(this->currentResolution == R_800_600){
					this->currentResolution = (R_TOTAL - 1);
				}
				else{
					this->currentResolution--;
				}
			}
			// Option == VOLUME MUSIC
			else if(this->currentOption == O_VOLUME_MUSIC){

			}
			// Option == VOLUME SFX
			else if(this->currentOption == O_VOLUME_SFX){

			}
			else {

			}

			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::RIGHT] == true){
		if(this->elapsedTime >= selectorDelayTime){
			// Option == Resolution
			if(this->currentOption == O_RESOLUTION){
				if(this->currentResolution == (R_TOTAL - 1)){
					this->currentResolution = R_800_600;
				}
				else{
					this->currentResolution++;
				}
			}
			// Option == VOLUME MUSIC
			else if(this->currentOption == O_VOLUME_MUSIC){

			}
			// Option == VOLUME SFX
			else if(this->currentOption == O_VOLUME_SFX){

			}
			else {

			}

			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::SPACE] == true && this->currentOption == O_APPLY){
		applyOptions();
	}

	if(keyStates[GameKeys::SPACE] == true && this->currentOption == O_RETURN){
		Game::instance().setState(Game::GStates::MENU);
	}
}

void GStateOptions::render(){
	if(this->optionsImage != nullptr){
		this->optionsImage->render(0, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set for the options screen!";
	}

	// if(this->resolutions[this->currentResolution] != nullptr){
	// 	this->resolutions[this->currentResolution]->render(650, 400);
	// }
	// else{
	// 	Log(WARN) << "No image set for the current resolution!";
	// }

	if(this->selector != nullptr){
		this->selector->render(selectorXPositionLeft[currentOption],
			selectorYPositionLeft[currentOption], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);

		this->selector->render(selectorXPositionRight[currentOption],
			selectorYPositionRight[currentOption], nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else{
		Log(WARN) << "No image set for the selector.";
	}

}

void GStateOptions::load(){
	Log(DEBUG) << "Loading options...";

	LuaScript luaOptions("lua/Options.lua");
	const std::string pathOptions = luaOptions.unlua_get<std::string>("options.images.dummy");
	const std::string pathCursor = luaOptions.unlua_get<std::string>("options.images.cursor");

	this->currentResolution = R_800_600;
	this->currentOption = O_RESOLUTION;
	
    this->optionsImage = Game::instance().getResources().get(pathOptions);
    this->selector = Game::instance().getResources().get(pathCursor);

    this->selector->setWidth(50);

    this->resolutions[R_800_600] = Game::instance().getResources().get("res/images/800x600.png");
    this->resolutions[R_768_432] = Game::instance().getResources().get("res/images/768x432.png");
    this->resolutions[R_960_540] = Game::instance().getResources().get("res/images/960x540.png");
}

void GStateOptions::unload(){
	Log(DEBUG) << "\tUnloading options...";
	cleanEntities();
}

void GStateOptions::applyOptions(){
	// Apply resolution
	if(this->currentResolution == R_800_600){
		Game::instance().resizeWindow(800, 600);
	}
	else if(this->currentResolution == R_768_432){
		Game::instance().resizeWindow(768, 432);
	}
	else if(this->currentResolution == R_960_540){
		Game::instance().resizeWindow(960, 540);
	}

	// Apply volume music
	Game::instance().getAudioHandler().setMusicVolume(100);

	// Apply volume sfx
	Game::instance().getAudioHandler().setEffectVolume(100);

}

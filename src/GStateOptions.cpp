#include "GStateOptions.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateOptions::GStateOptions() :
	elapsedTime(0.0),
	optionsImage(nullptr)
{
	this->currentResolution = R_800_600;

	for(unsigned int i = 0; i < R_TOTAL; i++){
		this->resolutions[i] = nullptr;
	}
}

GStateOptions::~GStateOptions(){

}

void GStateOptions::update(const double dt_){
	this->elapsedTime += dt_;

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::LATTACK] == true){
		Game::instance().setState(Game::GStates::MENU);
	}

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::LEFT] == true){
		if(this->elapsedTime >= selectorDelayTime){
			if(this->currentResolution == R_800_600){
				this->currentResolution = (R_TOTAL - 1);
			}
			else{
				this->currentResolution--;
			}
			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::RIGHT] == true){
		if(this->elapsedTime >= selectorDelayTime){
			if(this->currentResolution == (R_TOTAL - 1)){
				this->currentResolution = R_800_600;
			}
			else{
				this->currentResolution++;
			}
			this->elapsedTime = 0.0;
		}
	}

	if(keyStates[GameKeys::SPACE] == true){
		if(this->currentResolution == R_800_600){
			Game::instance().resizeWindow(800, 600);
		}
		else if(this->currentResolution == R_960_540){
			Game::instance().resizeWindow(960, 540);
		}
		
	}
}

void GStateOptions::render(){
	if(this->optionsImage != nullptr){
		this->optionsImage->render(0, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set for the options screen!";
	}

	if(this->resolutions[this->currentResolution] != nullptr){
		this->resolutions[this->currentResolution]->render(0, 0);
	}
	else{
		Log(WARN) << "No image set for the current resolution!";
	}
}

void GStateOptions::load(){
	Log(DEBUG) << "Loading options...";

	LuaScript luaOptions("lua/Options.lua");
	const std::string pathOptions = luaOptions.unlua_get<std::string>("options.images.dummy");
	
    this->optionsImage = Game::instance().getResources().get(pathOptions);

    this->resolutions[R_800_600] = Game::instance().getResources().get("res/images/800x600.png");
    this->resolutions[R_960_540] = Game::instance().getResources().get("res/images/960x540.png");
}

void GStateOptions::unload(){
	Log(DEBUG) << "\tUnloading options...";
	cleanEntities();
}

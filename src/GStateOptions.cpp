#include "GStateOptions.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateOptions::GStateOptions() :
	optionsImage(nullptr)
{

}

GStateOptions::~GStateOptions(){

}

void GStateOptions::update(const double dt_){
	(void(dt_)); //unused

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}
}

void GStateOptions::load(){
	Log(DEBUG) << "Loading options...";

	LuaScript luaOptions("lua/Options.lua");
	const std::string pathOptions = luaOptions.unlua_get<std::string>("options.images.dummy");
	
    this->optionsImage = Game::instance().getResources().get(pathOptions);
}

void GStateOptions::unload(){
	Log(DEBUG) << "\tUnloading options...";
	cleanEntities();
}

void GStateOptions::render(){
	if(this->optionsImage != nullptr){
		this->optionsImage->render(0, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set for the options screen!";
	}
}

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
	Logger::verbose("Loading options...");

	LuaScript luaOptions("lua/Options.lua");
	const std::string optionsPath = luaOptions.unlua_get<std::string>("options.spritePath");
	
    this->optionsImage = Game::instance().getResources().get(optionsPath);
}

void GStateOptions::unload(){
	Logger::verbose("\tUnloading options...");
	cleanEntities();
}

void GStateOptions::render(){
	if(this->optionsImage != nullptr){
		this->optionsImage->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No image set for the options screen!");
	}
}

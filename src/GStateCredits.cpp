#include "GStateCredits.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateCredits::GStateCredits() :
	creditsImage(nullptr)
{

}

GStateCredits::~GStateCredits(){

}

void GStateCredits::update(const double dt_){
	(void(dt_)); //unused

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}
}

void GStateCredits::load(){
	Logger::verbose("Loading credits...");

	LuaScript luaCredits("lua/Credits.lua");
	const std::string pathCredits = luaCredits.unlua_get<std::string>("credits.images.dummy");
	
    this->creditsImage = Game::instance().getResources().get(pathCredits);
}

void GStateCredits::unload(){
	Logger::verbose("\tUnloading credits...");
	cleanEntities();
}

void GStateCredits::render(){
	if(this->creditsImage != nullptr){
		this->creditsImage->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No image set for the options screen!");
	}
}

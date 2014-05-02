#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateMenu::GStateMenu() :
	menuImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

GStateMenu::~GStateMenu(){

}

void GStateMenu::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}

}

void GStateMenu::load(){
	Logger::verbose("Loading menu...");

	LuaScript luaMenu("lua/Menu.lua");
	const std::string menuPath = luaMenu.unlua_get<std::string>("menu.spritePath");
	const double luaLifeTime = luaMenu.unlua_get<double>("menu.lifeTime");

	this->menuImage = new Sprite(menuPath);
	this->lifeTime = luaLifeTime;
}

void GStateMenu::unload(){
	if(this->menuImage != nullptr){
		delete this->menuImage;
		this->menuImage = nullptr;
	}

	cleanEntities();
}

void GStateMenu::render(){
	if(this->menuImage != nullptr){
		this->menuImage->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No background set for the splash screen!");
	}
}

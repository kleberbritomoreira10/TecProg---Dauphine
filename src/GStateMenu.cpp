#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

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
		Game::setState((*Game::levelOne));
	}

}

void GStateMenu::load(){
	LuaScript luaSplash("lua/Menu.lua");
	const string splashPath = luaSplash.unlua_get<string>("menu.spritePath");
	const double luaLifeTime = luaSplash.unlua_get<double>("menu.lifeTime");

	Sprite* lSplash = new Sprite(splashPath);
	this->menuImage = lSplash;

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

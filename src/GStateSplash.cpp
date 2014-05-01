#include "GStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

GStateSplash::GStateSplash() :
	splash(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

GStateSplash::~GStateSplash(){

}

void GStateSplash::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::setState((*Game::menu));
	}

}

void GStateSplash::load(){
	LuaScript luaSplash("lua/Splash.lua");
	const string splashPath = luaSplash.unlua_get<string>("splash.spritePath");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	Sprite* lSplash = new Sprite(splashPath);
	this->splash = lSplash;

	this->lifeTime = luaLifeTime;
}

void GStateSplash::unload(){
	if(this->splash != nullptr){
		delete this->splash;
		this->splash = nullptr;
	}

	cleanEntities();
}

void GStateSplash::render(){
	if(this->splash != nullptr){
		this->splash->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No background set for the splash screen!");
	}
}

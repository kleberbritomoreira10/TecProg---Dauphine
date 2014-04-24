#include "StateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

StateSplash::StateSplash() :
	splash(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

StateSplash::~StateSplash(){

}

void StateSplash::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::setState((*Game::levelOne));
	}

}

void StateSplash::load(){
	LuaScript luaSplash("lua/Splash.lua");
	const string splashPath = luaSplash.unlua_get<string>("splash.spritePath");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	Sprite* lSplash = new Sprite(splashPath);
	this->splash = lSplash;

	this->lifeTime = luaLifeTime;
}

void StateSplash::unload(){
	if(this->splash != nullptr){
		this->splash->free();
		delete this->splash;
		this->splash = nullptr;
	}

	cleanEntities();
}

void StateSplash::render(){
	if(this->splash != nullptr){
		this->splash->render(0, 0);
	}
	else{
		Logger::warning("No background set for the splash screen!");
	}
}

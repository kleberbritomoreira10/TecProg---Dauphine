#include "StateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

StateSplash::StateSplash() :
	splash(nullptr),
	passedTime(0),
	lifeTime(0)
{
	LuaScript *luaSplash = new LuaScript("lua/Splash.lua");
	const string splashPath = luaSplash->unlua_get<string>("splash.spritePath");
	const double luaLifeTime = luaSplash->unlua_get<double>("splash.lifeTime");

	Sprite *lSplash = new Sprite(splashPath);
	this->splash = lSplash;

	this->lifeTime = luaLifeTime;

	load();
}

StateSplash::~StateSplash(){
	unload();
}

void StateSplash::load(){
	
}

void StateSplash::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::setState((*Game::levelOne));
	}

}

void StateSplash::unload(){
	this->splash->free();
	delete this->splash;
	this->splash = nullptr;
}

void StateSplash::render(){
	//if null,
	this->splash->render(0, 0);
}

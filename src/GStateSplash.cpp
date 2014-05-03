#include "GStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateSplash::GStateSplash() :
	current(0),
	passedTime(0.0),
	lifeTime(0.0)
{
	for(unsigned int i = 0; i < NUMBER_OF_SPLASH_IMAGES; i++){
		this->images[i] = nullptr;
	}
}

GStateSplash::~GStateSplash(){

}

void GStateSplash::update(const double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		if(this->current >= NUMBER_OF_SPLASH_IMAGES - 1){
			Game::instance().setState(Game::GStates::MENU);
		}
		else{
			this->passedTime = 0;
			this->current++;
		}
	}

}

void GStateSplash::load(){
	Logger::verbose("Loading splash screens...");

	LuaScript luaSplash("lua/Splash.lua");
	const std::string logoPath = luaSplash.unlua_get<std::string>("splash.spriteLogo");
	const std::string techsPath = luaSplash.unlua_get<std::string>("splash.spriteTechs");
	const std::string licensesPath = luaSplash.unlua_get<std::string>("splash.spriteLicenses");
	const std::string esrbPath = luaSplash.unlua_get<std::string>("splash.spriteEsrb");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	this->images[0] = Game::instance().getResources().get(logoPath);
	this->images[1] = Game::instance().getResources().get(techsPath);
	this->images[2] = Game::instance().getResources().get(licensesPath);
	this->images[3] = Game::instance().getResources().get(esrbPath);

	this->lifeTime = luaLifeTime;
}

void GStateSplash::unload(){
	Logger::verbose("\tUnloading splash screens...");
	this->current = 0;
	cleanEntities();
}

void GStateSplash::render(){
	if(this->images[this->current] != nullptr){
		this->images[this->current]->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No image set for the splash screen!");
	}
}

#include "GStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

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

void GStateSplash::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		if(this->current >= NUMBER_OF_SPLASH_IMAGES - 1){
			Game::setState((*Game::menu));
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
	const string logoPath = luaSplash.unlua_get<string>("splash.spriteLogo");
	const string techsPath = luaSplash.unlua_get<string>("splash.spriteTechs");
	const string licensesPath = luaSplash.unlua_get<string>("splash.spriteLicenses");
	const string esrbPath = luaSplash.unlua_get<string>("splash.spriteEsrb");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	this->images[0] = new Sprite(logoPath);
	this->images[1] = new Sprite(techsPath);
	this->images[2] = new Sprite(licensesPath);
	this->images[3] = new Sprite(esrbPath);

	this->lifeTime = luaLifeTime;
}

void GStateSplash::unload(){
	this->current = 0;

	for(unsigned int i = 0; i < NUMBER_OF_SPLASH_IMAGES; i++){
		delete this->images[i];
		this->images[i] = nullptr;
	}

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

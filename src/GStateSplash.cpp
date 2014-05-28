#include "GStateSplash.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateSplash::GStateSplash() :
	current(0),
	passedTime(0.0),
	lifeTime(0.0),
	ix(-300)
{
	for(unsigned int i = 0; i < NUMBER_OF_SPLASH_IMAGES; i++){
		this->images[i] = nullptr;
	}
}

GStateSplash::~GStateSplash(){

}

void GStateSplash::update(const double dt_){
	this->passedTime += dt_;

	if(this->ix < 0){
		this->ix += 5;
	}


	if(this->passedTime >= this->lifeTime){
		if(this->current >= NUMBER_OF_SPLASH_IMAGES - 1){
			Game::instance().setState(Game::GStates::MENU);
		}
		else{
			this->passedTime = 0;
			this->ix = -300;
			this->current++;
		}
	}

}

void GStateSplash::load(){
	Log(DEBUG) << "Loading splash screens...";

	LuaScript luaSplash("lua/Splash.lua");
	const std::string pathLogo = luaSplash.unlua_get<std::string>("splash.images.alke");
	const std::string pathTechs = luaSplash.unlua_get<std::string>("splash.images.techs");
	const std::string pathLicenses = luaSplash.unlua_get<std::string>("splash.images.licenses");
	const std::string pathEsrb = luaSplash.unlua_get<std::string>("splash.images.esrb");
	const double luaLifeTime = luaSplash.unlua_get<double>("splash.lifeTime");

	this->images[0] = Game::instance().getResources().get(pathLogo);
	this->images[1] = Game::instance().getResources().get(pathTechs);
	this->images[2] = Game::instance().getResources().get(pathLicenses);
	this->images[3] = Game::instance().getResources().get(pathEsrb);

	this->lifeTime = luaLifeTime;
}

void GStateSplash::unload(){
	Log(DEBUG) << "\tUnloading splash screens...";
	this->current = 0;
	cleanEntities();
}

void GStateSplash::render(){
	if(this->images[this->current] != nullptr){
		this->images[this->current]->render(this->ix, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set for the splash screen!";
	}
}

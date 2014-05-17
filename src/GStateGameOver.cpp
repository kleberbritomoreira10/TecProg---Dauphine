#include "GStateGameOver.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateGameOver::GStateGameOver() :
	gameOverImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

GStateGameOver::~GStateGameOver(){

}

void GStateGameOver::update(const double dt_){
	this->passedTime += dt_;
}

void GStateGameOver::load(){
	Logger::verbose("Loading Game Over...");

	LuaScript luaGameOver("lua/GameOver.lua");
	const std::string gameOverPath = luaGameOver.unlua_get<std::string>("gameOver.spritePath");
	const double luaLifeTime = luaGameOver.unlua_get<double>("gameOver.lifeTime");

    this->gameOverImage = Game::instance().getResources().get(gameOverPath);
	this->lifeTime = luaLifeTime;
}

void GStateGameOver::unload(){
	Logger::verbose("\tUnloading Game Over...");
	cleanEntities();
}

void GStateGameOver::render(){
	if(this->gameOverImage != nullptr){
		this->gameOverImage->render(0, 0, nullptr, true);
	}
	else{
		Logger::warning("No image set for the game over screen!");
	}
}

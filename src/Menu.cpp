#include "Menu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>
using std::string;

Menu::Menu() :
	menu(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

Menu::~Menu(){

}

void Menu::update(double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::setState((*Game::levelOne));
	}

}

void Menu::load(){
	LuaScript luaSplash("lua/Menu.lua");
	const string splashPath = luaSplash.unlua_get<string>("menu.spritePath");
	const double luaLifeTime = luaSplash.unlua_get<double>("menu.lifeTime");

	Sprite* lSplash = new Sprite(splashPath);
	this->menu = lSplash;

	this->lifeTime = luaLifeTime;
}

void Menu::unload(){
	if(this->menu != nullptr){
		delete this->menu;
		this->menu = nullptr;
	}

	cleanEntities();
}

void Menu::render(){
	if(this->menu != nullptr){
		this->menu->render(0, 0);
	}
	else{
		Logger::warning("No background set for the splash screen!");
	}
}

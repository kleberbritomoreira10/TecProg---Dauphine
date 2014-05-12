#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"


#include <string>

GStateMenu::GStateMenu() :
	menuImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0),
	selectorXPositionLeft {430, 455, 455, 470},
	selectorYPositionLeft {360, 410, 465, 510},
	selectorXPositionRight {680, 650, 650, 640},
	selectorYPositionRight {360, 410, 465, 510},
	selectorPosition(0)
{

}

GStateMenu::~GStateMenu(){

}

void GStateMenu::update(const double dt_){
	this->passedTime += dt_;
	handleSelectorMenu();	
}

void GStateMenu::load(){
	Logger::verbose("Loading menu...");

	LuaScript luaMenu("lua/Menu.lua");
	const std::string menuPath = luaMenu.unlua_get<std::string>("menu.spritePath");
	const std::string cursorPath = luaMenu.unlua_get<std::string>("menu.cursorPath");
	const double luaLifeTime = luaMenu.unlua_get<double>("menu.lifeTime");

    this->menuImage = Game::instance().getResources().get(menuPath);
    this->menuSelector = Game::instance().getResources().get(cursorPath);
	this->lifeTime = luaLifeTime;
}

void GStateMenu::unload(){
	Logger::verbose("\tUnloading menu...");
	cleanEntities();
}

void GStateMenu::render(){
	if(this->menuImage != nullptr){
		this->menuImage->render(0, 0, nullptr, true);

		this->menuSelector->setWidth(50);
		this->menuSelector->setHorizontalFlip(false);
		this->menuSelector->render(selectorXPositionLeft[selectorPosition], selectorYPositionLeft[selectorPosition], nullptr, false);
		this->menuSelector->setHorizontalFlip(true);
		this->menuSelector->render(selectorXPositionRight[selectorPosition], selectorYPositionRight[selectorPosition], nullptr, false );
	}
	else{
		Logger::warning("No background set for the splash screen!");
	}
}

void GStateMenu::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const float selectorDelayTime = 0.2;
	const int cursorFirstPositioin = 0;
	const int cursorLastPositioin = 3;


	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::LEFT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(selectorPosition < cursorLastPositioin){
				selectorPosition++;
			}
			else{
				selectorPosition = cursorFirstPositioin;
			}
			this->passedTime = 0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::RIGHT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(selectorPosition > cursorFirstPositioin){
				selectorPosition--;
			}
			else{
				selectorPosition = cursorLastPositioin;
			}
			this->passedTime = 0;
		}
	}
	else if(keyStates[GameKeys::SPACE] == true && selectorPosition == 0){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}
}
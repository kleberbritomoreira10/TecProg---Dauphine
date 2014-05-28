#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateMenu::GStateMenu() :
	menuImage(nullptr),
	passedTime(0.0),
	currentSelection(Selection::NEWGAME),
	selectorXPositionLeft {430, 455, 455, 470},
	selectorYPositionLeft {360, 410, 465, 510},
	selectorXPositionRight {680, 650, 650, 640},
	selectorYPositionRight {360, 410, 465, 510}
{

}

GStateMenu::~GStateMenu(){

}

void GStateMenu::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().stop();
	}

}

void GStateMenu::load(){
	Logger::verbose("Loading menu...");

	LuaScript luaMenu("lua/Menu.lua");
	const std::string pathTitleScreen = luaMenu.unlua_get<std::string>("menu.images.titleScreen");
	const std::string pathCursor = luaMenu.unlua_get<std::string>("menu.images.cursor");

    this->menuImage = Game::instance().getResources().get(pathTitleScreen);
    this->menuSelector = Game::instance().getResources().get(pathCursor);
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
		this->menuSelector->render(selectorXPositionLeft[currentSelection],
			selectorYPositionLeft[currentSelection], nullptr, false);

		this->menuSelector->setHorizontalFlip(true);
		this->menuSelector->render(selectorXPositionRight[currentSelection],
			selectorYPositionRight[currentSelection], nullptr, false);

	}
	else{
		Logger::warning("No image set to display on the menu!");
	}
}

void GStateMenu::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection < (Selection::TOTAL - 1)){
				currentSelection++;
			}
			else{
				currentSelection = Selection::NEWGAME;
			}
			this->passedTime = 0.0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection > Selection::NEWGAME){
				currentSelection--;
			}
			else{
				currentSelection = (Selection::TOTAL - 1);
			}
			this->passedTime = 0.0;
		}
	}
	else if(currentSelection == Selection::NEWGAME && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}
	else if(currentSelection == Selection::OPTIONS && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::OPTIONS);
	}
	else if(currentSelection == Selection::CREDITS && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::CREDITS);
	}
}

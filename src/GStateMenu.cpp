#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateMenu::GStateMenu() :
	menuImage(nullptr),
	passedTime(0.0),
	currentSelection(Selection::NEWGAME),
	selectorXPositionLeft {610, 635, 635, 645},
	selectorYPositionLeft {560, 625, 690, 755},
	selectorXPositionRight {880, 855, 855, 845},
	selectorYPositionRight {560, 625, 690, 755}
{

}

GStateMenu::~GStateMenu(){

}

void GStateMenu::load(){
	Log(DEBUG) << "Loading menu...";

	LuaScript luaMenu("lua/Menu.lua");
	const std::string pathTitleScreen = luaMenu.unlua_get<std::string>("menu.images.titleScreen");
	const std::string pathCursor = luaMenu.unlua_get<std::string>("menu.images.cursor");

    this->menuImage = Game::instance().getResources().get(pathTitleScreen);
    this->menuSelector = Game::instance().getResources().get(pathCursor);

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateMenu::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();
}

void GStateMenu::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().stop();
	}

}

void GStateMenu::render(){
	if(this->menuImage != nullptr){
		this->menuImage->render(0, 0, nullptr, true);

		this->menuSelector->setWidth(50);

		this->menuSelector->render(selectorXPositionLeft[currentSelection],
			selectorYPositionLeft[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);

		this->menuSelector->render(selectorXPositionRight[currentSelection],
			selectorYPositionRight[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);

	}
	else{
		Log(WARN) << "No image set to display on the menu!";
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
		Game::instance().setState(Game::GStates::NEW_GAME);
		//Game::instance().setState(Game::GStates::LEVEL_ONE);
	}

	else if(currentSelection == Selection::CONTINUE && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::CONTINUE);
	}

	else if(currentSelection == Selection::OPTIONS && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::OPTIONS);
	}

	else if(currentSelection == Selection::CREDITS && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::CREDITS);
	}
}

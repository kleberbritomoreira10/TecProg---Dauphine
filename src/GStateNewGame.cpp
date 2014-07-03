#include "GStateNewGame.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateNewGame::GStateNewGame() :
	background(nullptr),
	selector(nullptr),
	passedTime(0.0),
	currentSelection(Selection::SLOT_1),
	selectorXPosition(562),
	selectorYPosition {500,610,723}
{

}

GStateNewGame::~GStateNewGame(){

}

void GStateNewGame::load(){
	Log(DEBUG) << "Loading Choose Slot Screen...";

	//As is uses the same resources as the Continue screen...
	LuaScript luaMenu("lua/Continue.lua");
	const std::string pathBackground = luaMenu.unlua_get<std::string>("continue.images.background");
	const std::string pathSelector = luaMenu.unlua_get<std::string>("continue.images.selector");

	this->background = Game::instance().getResources().get(pathBackground);
    this->selector = Game::instance().getResources().get(pathSelector);

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateNewGame::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();
}

void GStateNewGame::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}

}

void GStateNewGame::render(){

	if(this->background != nullptr){
		this->background->render(0, 0, nullptr, true);

		this->selector->setWidth(410);
		this->selector->setHeight(102);

		this->selector->render(selectorXPosition, selectorYPosition[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else{
		Log(WARN) << "No image set to display on the menu!";
	}
}

void GStateNewGame::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::LATTACK] == true){
		if(this->passedTime >= selectorDelayTime){
			Game::instance().setState(Game::GStates::MENU);
		}
	}
	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection < (Selection::TOTAL - 1)){
				currentSelection++;
			}
			else{
				currentSelection = Selection::SLOT_1;
			}
			this->passedTime = 0.0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection > Selection::SLOT_1){
				currentSelection--;
			}
			else{
				currentSelection = (Selection::TOTAL - 1);
			}
			this->passedTime = 0.0;
		}
	}
	else if(currentSelection == Selection::SLOT_1 && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}
	else if(currentSelection == Selection::SLOT_2 && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}
	else if(currentSelection == Selection::SLOT_3 && keyStates[GameKeys::SPACE] == true){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}

}

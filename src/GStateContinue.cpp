#include "GStateContinue.h"
#include "LuaScript.h"
#include "Game.h"
#include "Util.h"
#include <string>

GStateContinue::GStateContinue() :
	background(nullptr),
	selector(nullptr),
	passedTime(0.0),
	currentSelection(Selection::SLOT_1),
	selectorXPosition(562),
	selectorYPosition {500,610,723}
{
	this->slot1 = new Text(615.0, // x
							520.0, // y
							"res/fonts/maturasc.ttf", // font path
							45, // size
							"Empty Slot", // text
							{0xCE, 0XCE, 0XCE, 255}); // sdl_color

	this->slot2 = new Text(615.0, // std::string slot1Text;std::string slot1Text;x
							630.0, // y
							"res/fonts/maturasc.ttf", // font path
							45, // size
							"Empty Slot", // text
							{0xCE, 0XCE, 0XCE, 255}); // sdl_color

	this->slot3 = new Text(615.0, // x
							730.0, // y
							"res/fonts/maturasc.ttf", // font path
							45, // size
							"Empty Slot", // text
							{0xCE, 0XCE, 0XCE, 255}); // sdl_color


}

GStateContinue::~GStateContinue(){

}

void GStateContinue::load(){
	Log(DEBUG) << "Loading Continue Screen...";
	
	if(Game::instance().getSaves().isSaved(SLOT_1)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_1);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
			this->slot1->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
		else
			this->slot1->changeText(currentLevel.c_str(), {0xCE, 0xCE, 0xCE, 255});
	}

	else{
		this->slot1->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
	}


	if(Game::instance().getSaves().isSaved(SLOT_2)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_2);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
			this->slot2->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
		else
			this->slot2->changeText(currentLevel.c_str(), {0xCE, 0xCE, 0xCE, 255});
	}
	else{
		this->slot2->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
	}


	if(Game::instance().getSaves().isSaved(SLOT_3)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_3);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
			
		if(levelFromSave == -1)
			this->slot3->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
		else
			this->slot3->changeText(currentLevel.c_str(), {0xCE, 0xCE, 0xCE, 255});
	}
	else{
		this->slot3->changeText("Empty Slot", {0xCE, 0xCE, 0xCE, 255});
	}

	LuaScript luaMenu("lua/Continue.lua");
	const std::string pathBackground = luaMenu.unlua_get<std::string>("continue.images.background");
	const std::string pathSelector = luaMenu.unlua_get<std::string>("continue.images.selector");

	this->background = Game::instance().getResources().get(pathBackground);
    this->selector = Game::instance().getResources().get(pathSelector);

	this->selector->setWidth(410);
	this->selector->setHeight(102);

    this->currentSelection = Selection::SLOT_1;

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateContinue::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();
}

void GStateContinue::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}

}

void GStateContinue::render(){

	if(this->background != nullptr){
		this->background->render(0, 0, nullptr, true);

		this->selector->render(selectorXPosition, selectorYPosition[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);
	
		this->slot1->render(0, 0);
		this->slot2->render(0, 0);
		this->slot3->render(0, 0);


	}
	else{
		Log(WARN) << "No image set to display on the menu!";
	}
}

void GStateContinue::handleSelectorMenu(){
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
		Game::instance().currentSlot = SLOT_1;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_1)){
			case 1:
				Game::instance().setState(Game::GStates::LEVEL_ONE);
			break;
			case 2:
				Game::instance().setState(Game::GStates::LEVEL_TWO);
			break;
			case 6:
				Game::instance().setState(Game::GStates::LEVEL_BOSS);
			break;
		}
	}
	else if(currentSelection == Selection::SLOT_2 && keyStates[GameKeys::SPACE] == true){
		Game::instance().currentSlot = SLOT_2;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_2)){
			case 1:
				Game::instance().setState(Game::GStates::LEVEL_ONE);
			break;
			case 2:
				Game::instance().setState(Game::GStates::LEVEL_TWO);
			break;
			case 6:
				Game::instance().setState(Game::GStates::LEVEL_BOSS);
			break;
		}
	}
	else if(currentSelection == Selection::SLOT_3 && keyStates[GameKeys::SPACE] == true){
		Game::instance().currentSlot = SLOT_3;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_3)){
			case 1:
				Game::instance().setState(Game::GStates::LEVEL_ONE);
			break;
			case 2:
				Game::instance().setState(Game::GStates::LEVEL_TWO);
			break;
			case 6:
				Game::instance().setState(Game::GStates::LEVEL_BOSS);
			break;
		}
	}

}

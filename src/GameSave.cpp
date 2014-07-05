#include "GameSave.h"
#include "Logger.h"
#include <stdlib.h>

GameSave& GameSave::instance(){
	static GameSave* instance = new GameSave();
	return *instance;
}

GameSave::GameSave(){
	Log(DEBUG) << "Saving level";
}

void GameSave::createSaveGameFile(int saveSelection_){
	this->saveSelection = saveSelection_;
	if(this->saveSelection == 0){
		this->saveFile.open("saveSlot1.dauphine");
	}
	else if(this->saveSelection == 1){
		this->saveFile.open("saveSlot2.dauphine");
	}
	else if(this->saveSelection == 2){
		this->saveFile.open("saveSlot3.dauphine");
	}
}	

void GameSave::saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies){
	this->currentLevel = level_;
	this->saveFile << this->currentLevel << std::endl;
	this->saveFile << player->x << " " << player->y << std::endl;
	this->saveFile << enemies.size();
	this->saveFile.close();
}

int GameSave::getSavedLevel(int continueSelection_){
	this->saveSelection = continueSelection_;
	std::string level;
	if(this->saveSelection == 0){
		this->continueFile.open("saveSlot1.dauphine");
	}
	else if(this->saveSelection == 1){
		this->continueFile.open("saveSlot2.dauphine");
	}
	else if(this->saveSelection == 2){
		this->continueFile.open("saveSlot3.dauphine");
	}
	this->continueFile >> level;
	return std::stoi(level);
}

void GameSave::restorePlayerPosition(Player* player_){
	double playerX_= 0;
	double playerY_ = 0;
	
	if(!this->continueFile.fail()){
		this->continueFile >> playerX_;
		this->continueFile >> playerY_;

		player_->x = playerX_;
		player_->y = playerY_;
		this->continueFile.close();	
	}
	else{
		Log(DEBUG) << "No save in this level";
	}
}
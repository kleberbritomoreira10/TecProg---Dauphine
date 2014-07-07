#include "GameSave.h"
#include "Logger.h"
#include <cstdlib>

GameSave::GameSave(){

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
	this->saveFile.close();
}	

void GameSave::saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies){
	createSaveGameFile(this->saveSelection);
	this->currentLevel = level_;
	this->saveFile << this->currentLevel << std::endl;
	this->saveFile << player->x << " " << player->y << std::endl;
	this->saveFile << enemies.size() << std::endl;
	for(auto enemy : enemies){
		this->saveFile << enemy->isDead() << " ";
	}
	this->saveFile.close();
}

int GameSave::getSavedLevel(int continueSelection_){
	this->saveSelection = continueSelection_;
	std::string level = "-1";

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

bool GameSave::isSaved(const int saveSlot_){

	if(saveSlot_ == 0){
		this->continueFile.open("saveSlot1.dauphine");
		this->continueFile.close();
	}
	else if(saveSlot_ == 1){
		this->continueFile.open("saveSlot2.dauphine");
		this->continueFile.close();
	}
	else if(saveSlot_ == 2){
		this->continueFile.open("saveSlot3.dauphine");
		this->continueFile.close();
	}	
	return !this->continueFile.fail();
}

void GameSave::restorePlayerPosition(Player* player_){
	double playerX_= 0;
	double playerY_= 0;
	
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
#include "GameSave.h"
#include "Logger.h"

GameSave& GameSave::instance(int saveSelection_){
	static GameSave* instance = new GameSave(saveSelection_);
	return *instance;
}

GameSave::GameSave(int saveSelection_){
	this->saveSelection = saveSelection_;
	Log(DEBUG) << "Saving level";
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

void GameSave::saveLevel(unsigned int level_, Player* player){
	this->currentLevel = level_;
	this->saveFile << this->currentLevel << endl;
	this->saveFile << player->x << " " << player->y << endl;
	this->saveFile.close();
}
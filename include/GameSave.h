#ifndef INCLUDE_GAMESAVE_H
#define INCLUDE_GAMESAVE_H

#include <fstream>
#include "Player.h"
#include "Enemy.h"

class GameSave {

	public:

		static GameSave& instance();
		GameSave();

		void createSaveGameFile(int saveSelection_);
		void saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies);

		int saveSelection;
		unsigned int currentLevel;

		std::ofstream saveFile;
};

#endif //INCLUDE_GAMESAVE_H
#ifndef INCLUDE_GAMESAVE_H
#define INCLUDE_GAMESAVE_H

#include <fstream>
#include "Player.h"

class GameSave {

	public:

		GameSave& GameSave::instance(int saveSelection_);
		GameSave(int saveSelection_);

		void saveLevel(unsigned int level_, Player* player);

		int saveSelection;
		unsigned int currentLevel;

		std::ofstream saveFile;
};

#endif //INCLUDE_GAMESAVE_H
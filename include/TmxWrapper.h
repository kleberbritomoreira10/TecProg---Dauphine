#ifndef INCLUDE_TMXWRAPPER_H
#define INCLUDE_TMXWRAPPER_H

#include "../lib/TmxParser/Tmx.h"
#include <string>
#include <vector>

class TmxWrapper {

	public:
		TmxWrapper(const std::string& path_);
		~TmxWrapper();
		void setFile(const std::string& path_);
		std::vector<int> getTileData();
		int getMapWidth();
		int getMapHeight();

	private:
		Tmx::Map* map;

};

#endif // INCLUDE_TMXWRAPPER_H

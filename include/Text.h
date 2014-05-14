#ifndef INCLUDE_TEXT_H
#define INCLUDE_TEXT_H

#include "SDLWrapper.h"

class Text{
	public:
		Text(const std::string& path_,const int size_);
		~Text();
		void render();
	private:
		Sprite* sprite;

};
#endif //INCLUDE_TEXT_H
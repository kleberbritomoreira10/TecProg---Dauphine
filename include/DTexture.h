#ifndef INCLUDE_DTEXTURE_H
#define INCLUDE_DTEXTURE_H

#include "SDLWrapper.h"
#include <string>

class DTexture {

	public:
		DTexture();
		~DTexture();

		bool loadFrom(std::string path, SDL_Renderer *renderer);
		void free();
		void render(int x, int y, SDL_Rect *clip = NULL);

		int width;
		int height;
		SDL_Renderer *renderer;
		SDL_Texture* sdlTexture;
};

#endif //INCLUDE_DTEXTURE_H

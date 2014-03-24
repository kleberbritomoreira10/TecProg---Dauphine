#ifndef INCLUDE_SPRITE_H
#define INCLUDE_SPRITE_H

#include "SDLWrapper.h"
#include <string>

using std::string;

class Sprite {

	public:
		/* Creates the Sprite, setting the desired renderer. */
		Sprite(SDL_Renderer *lRenderer);
		/* Destroys everything related to the Sprite. */
		~Sprite();

		/* Loads a SDL_Texture from the desired path. */
		bool loadFrom(string path);

		/* Frees everything but the renderer. */
		void free();
		/* Renders the Sprite at the x,y position. Optionally, clips the image. */
		void render(int x, int y, SDL_Rect *clip = nullptr);

		int width;
		int height;
		
	private:
		SDL_Renderer *sdlRenderer;
		SDL_Texture* sdlTexture;
};

#endif //INCLUDE_SPRITE_H

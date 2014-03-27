#ifndef INCLUDE_SPRITE_H
#define INCLUDE_SPRITE_H

#include "SDLWrapper.h"
#include <string>

using std::string;

class Sprite {

	public:
		/**
		* The constructor.
		* Creates the sprite, and sets the desired renderer.
		*/
		Sprite(SDL_Renderer *lRenderer);

		/**
		* The destructor.
		* Destroys everything related to the sprite.
		*/
		~Sprite();

		/**
		* Loads image from a path.
		* Given an existing path for an image, loads the SDL_Texture from it.
		* @params path : the image path.
		* @return whether the sprites SDL_Texture was set or not (null or not).
		*/
		bool loadFrom(string path);

		/**
		* Frees texture, if it exists.
		* If the texture already exists, frees everything but the set renderer.
		*/
		void free();

		/* Renders the Sprite at the x,y position. Optionally, clips the image. */
		/**
		* Renders the sprite.
		* Copy the SDL_Texture onto the renderer, at the desired x,y position.
		* @params x : x position on the screen.
		* @params y : y position on the screen.
		* @params clip : Clips the texture, on the SDL_Rect bounds. If null, renders the entire texture.
		*/
		void render(int x, int y, SDL_Rect *clip = nullptr);

		int width;
		int height;
		
	private:
		SDL_Renderer *sdlRenderer;
		SDL_Texture* sdlTexture;
};

#endif //INCLUDE_SPRITE_H

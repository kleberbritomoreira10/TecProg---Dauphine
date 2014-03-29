#ifndef INCLUDE_SPRITE_H
#define INCLUDE_SPRITE_H

#include "SDLWrapper.h"
#include <string>

using std::string;

/**
* Visual representation of game objects.
* Holds the SDL_Texture from the SDL2 library.
*/
class Sprite {

	public:
		/**
		* The constructor.
		* Initializes all the data, and sets the desired renderer.
		* @param lRenderer : The renderer you want the sprite to render onto.
		* @note If the lRenderer parameter is null, warns that the Sprite will not be renderable.
		*/
		Sprite(SDL_Renderer *lRenderer);

		/**
		* The destructor.
		* Calls the free method, and sets the renderer pointer to null.
		* @see free()
		*/
		~Sprite();

		/**
		* Loads image from a path.
		* Given an existing path for an image, loads the SDL_Texture from it.
		* @param path : the image path.
		* @return Whether the sprite's SDL_Texture (sdlTexture) is null or not.
		*/
		bool loadFrom(string path);

		/**
		* Frees texture, if it exists.
		* If the texture already exists, frees everything but the set renderer.
		*/
		void free();

		/**
		* Renders the sprite.
		* Copy the SDL_Texture onto the renderer, at the desired x,y position.
		* @param x : The position on the x axis of the screen.
		* @param y : The position on the y axis of the screen.
		* @param clip : Clips the texture, on the SDL_Rect bounds. If omitted, renders the entire texture.
		*/
		void render(double x, double y, SDL_Rect *clip = nullptr);

		/**
		* @return The Sprite width.
		*/
		unsigned int getWidth();

		/**
		* @return The Sprite height.
		*/
		unsigned int getHeight();
		
	private:
		SDL_Renderer *sdlRenderer; /**< The SDL renderer to render onto. */
		SDL_Texture* sdlTexture; /**< The SDL texture to use as the image. */
		unsigned int width; /**< The loaded image's width. */
		unsigned int height; /**< The loaded image's width. */
};

#endif //INCLUDE_SPRITE_H

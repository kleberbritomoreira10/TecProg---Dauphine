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
		* Initializes all the data, and sets the desired renderer. Loads image with the desired path.
		* @param renderer_ : The renderer you want the sprite to render onto.
		* @param path_ : the image path.
		* @note If the SDL_Renderer parameter is null, warns that the Sprite will not be renderable.
		* @see Sprite::loadFrom(string path_)
		*/
		Sprite(SDL_Renderer *renderer_, string path_);

		/**
		* The destructor.
		* Calls the free method, and sets the renderer pointer to null.
		* @see free()
		*/
		~Sprite();

		/**
		* Frees texture, if it exists.
		* If the texture already exists, frees everything but the set renderer.
		*/
		void free();

		/**
		* Renders the sprite.
		* Copy the SDL_Texture onto the renderer, at the desired x,y position.
		* @param x_ : The position on the x axis of the screen.
		* @param y_ : The position on the y axis of the screen.
		* @param clip_ : Clips the texture, on the SDL_Rect bounds. If omitted, renders entire texture.
		* @param angle_ : An angle in degrees that indicates the rotation that will be applied to the renderQuad. If omitted, no rotation will be applied.
		* @param center_ : A point indicating the point around which renderQuad will be rotated. If omitted, rotation will be done in width/height center.
		* @param flip_ : Value static which flipping actions should be performed on the texture.
		* @note The only obligatory parameters are x_ and y_.
		* @note If it fails to render, logs an error message.
		*/
		void render(double x_, double y_, SDL_Rect *clip_ = nullptr, double angle_ = 0.0, SDL_Point* center_ = nullptr, SDL_RendererFlip flip_ = SDL_FLIP_NONE);

		/**
		* @return The Sprite width.
		*/
		unsigned int getWidth();

		/**
		* @return The Sprite height.
		*/
		unsigned int getHeight();
		
	private:
		/**
		* Loads image from a path.
		* Given an existing path for an image, loads the SDL_Texture from it.
		* @param path_ : the image path.
		* @note Error message is logged if the sprite's SDL_Texture (sdlTexture) is null after method.
		*/
		void loadFrom(string path_);

		unsigned int width; /**< The loaded image's width. */
		unsigned int height; /**< The loaded image's width. */

		SDL_Renderer *sdlRenderer; /**< The SDL renderer to render onto. */
		SDL_Texture* sdlTexture; /**< The SDL texture to use as the image. */

};

#endif //INCLUDE_SPRITE_H

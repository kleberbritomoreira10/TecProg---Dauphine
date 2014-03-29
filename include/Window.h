#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "SDLWrapper.h"
#include <string>

using std::string;

/**
* Actual window that game runs on.
* Contains the SDL window and the SDL renderer, and methods related to these.
*/
class Window {

	public:
		/**
		* The constructor.
		* Sets all attributes, and calls the initialize method.
		* @param lWidth : The desired window width.
		* @param lHeight : The desired window height.
		* @param lTitle : The desired window title.
		* @note If omitted, window title will be "SDL Window".
		* @see initialize()
		*/
		Window(unsigned int lWidth, unsigned int lHeight, string lTitle = "SDL Window");

		/**
		* The destructor.
		* Uses the destroy method to delete window.
		* @see destroy()
		*/
		~Window();

		/**
		* Frees allocated members.
		* Frees the SDL_Renderer and the SDL_Window.
		*/
		void destroy();

		/**
		* Minimizes window.
		* Uses SDLs internal method to minimize the window.
		*/
		void minimize();

		/**
		* Maximizes window.
		* Uses SDLs internal method to maximize the window.
		*/
		void maximize();

		/**
		* Clears the renderer.
		* Sets the renderers draw color to black, and subsequently clears it.
		*/
		void clear();

		/**
		* Renders to screen.
		* Updates the screen with every change in the renderer.
		*/
		void render();

		/**
		* Rescales the renderization.
		* Set a device independent resolution for rendering.
		* @param lWidth : The new resolution width.
		* @param lHeight : The new resolution height.
		* @see SDL_RenderSetLogicalSize()
		*/
		void rescale(unsigned int lWidth, unsigned int lHeight);

		SDL_Renderer *renderer; /**< The SDL renderer to render onto. */

	private:
		SDL_Window *window; /**< The SDL window, that will be the actual game window. */
		unsigned int width; /**< The game Window width. */
		unsigned int height; /**< The game Window width. */
		string windowTitle; /**< The game Window title. */

		/**
		* Initializes the window and the renderer.
		* Creates the Window, with specified width, height and title.
		*/
		void initialize();
};

#endif //INCLUDE_WINDOW_H

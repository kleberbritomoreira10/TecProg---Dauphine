#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "SDLWrapper.h"

#include <string>
using std::string;

/**
* Represents actual window that game runs on.
* Contains the SDL_Window and the SDL_Renderer, and methods related to these.
*/
class Window {

	public:
		/**
		* The constructor.
		* Sets all attributes, and calls the initialize method.
		* @param width_ : The desired window width.
		* @param height_ : The desired window height.
		* @param title_ : The desired window title.
		* @note If omitted, window title will be "SDL Window".
		* @see Window::initialize
		*/
		Window(const unsigned int width_, const unsigned int height_,
			const string& title_ = "SDL Window");

		/**
		* The destructor.
		* Uses the destroy method to delete window.
		* @see Window::destroy
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
		* @param size_ : Multiplies Configuration::resolutionWidth and
		* 	Configuration::resolutionHeight for the new resolution.
		* @see SDL_RenderSetLogicalSize
		*/
		void rescale(unsigned int size_);

		/**
		* @return The renderer attribute.
		*/
		static SDL_Renderer* getRenderer();

	private:
		/**
		* Initializes the window and the renderer.
		* Creates the Window, with specified width, height and title.
		*/
		void initialize();
		
		unsigned int width; /**< The game Window width. */
		unsigned int height; /**< The game Window width. */
		const string windowTitle; /**< The game Window title. */

		SDL_Window *sdlWindow; /**< The SDL window, that will be the actual game window. */
		static SDL_Renderer *sdlRenderer; /**< The SDL renderer to render onto. */

		
};

#endif //INCLUDE_WINDOW_H

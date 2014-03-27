#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "SDLWrapper.h"
#include <string>

using std::string;

class Window {

	public:
		/**
		* The constructor.
		* Sets all attributes, and calls the initialize method.
		* @params lWidth : desired window width.
		* @params lHeight : desired window height.
		* @params lTitle : desired window title.
		* @see initialize()
		*/
		Window(unsigned int lWidth, unsigned int lHeight, string lTitle = "SDL Window");

		/**
		* The destructor.
		* Uses the destroy method to free window.
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
		* @params lWidth : the new resolution width.
		* @params lHeight : the new resolution height.
		*/
		void rescale(unsigned int lWidth, unsigned int lHeight);

		unsigned int width;
		unsigned int height;
		string windowTitle;

		SDL_Renderer *renderer;
		SDL_Window *window;

	private:
		/* Creates the Window, with specified width, height and title. */
		void initialize();
};

#endif //INCLUDE_WINDOW_H

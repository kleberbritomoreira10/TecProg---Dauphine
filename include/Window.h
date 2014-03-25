#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "SDLWrapper.h"
#include <string>

using std::string;

class Window {

	public:
		/* Sets all attributs, and calls initialize() */
		Window(unsigned int lWidth, unsigned int lHeight, string lTitle = "SDL Window");
		/* Uses destroy() to free Window. */
		~Window();

		/* Frees window and renderer. */
		void destroy();
		/* Minimizes the Window. */
		void minimize();
		/* Maximizes the Window. */
		void maximize();

		/* Clears the renderer. */
		void clear();
		/* Renders everything present in the renderer. */
		void render();
		/* Set a device independent resolution for rendering. */
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

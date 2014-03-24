#ifndef INCLUDE_WINDOW_H
#define INCLUDE_WINDOW_H

#include "SDLWrapper.h"
#include <string>

using std::string;

class Window {

	public:
		/* Creates the Window, with specified width, height and title. */
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

		unsigned int width;
		unsigned int height;
		string windowTitle;

		SDL_Renderer *renderer;
		SDL_Window *window;

};

#endif //INCLUDE_WINDOW_H

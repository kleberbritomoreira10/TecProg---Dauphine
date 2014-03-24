#include "Window.h"
#include "Logger.h"

Window::Window(unsigned int lWidth, unsigned int lHeight, string lTitle){
	this->window = nullptr;
	this->renderer = nullptr;
	this->width = lWidth;
	this->height = lHeight;
	this->windowTitle = lTitle;

	// Creates the SDL window.
	this->window = SDL_CreateWindow(this->windowTitle.c_str(), 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		this->width, this->height,
		SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(this->window != nullptr){

		//Creates the SDL renderer.
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		if(this->renderer != nullptr){

			Logger::log("Game successfully loaded.");
				
		}
		else{
			Logger::errorSDL("Renderer could not be created.", SDL_GetError());
		}
	}
	else{
		Logger::errorSDL("Window failed to be created.", SDL_GetError());
	}
}

Window::~Window(){
	destroy();
}

void Window::destroy(){
	// Destroys the Window renderer.
	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;

	// Destroys the Window window.
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
}

void Window::minimize(){
	SDL_MinimizeWindow(this->window);
}

void Window::maximize(){
	SDL_MaximizeWindow(this->window);
}

void Window::clear(){
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->renderer);
}

void Window::render(){
	SDL_RenderPresent(this->renderer);
}

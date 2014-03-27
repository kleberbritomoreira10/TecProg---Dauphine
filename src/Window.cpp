#include "Window.h"
#include "Logger.h"

Window::Window(unsigned int lWidth, unsigned int lHeight, string lTitle){
	this->window = nullptr;
	this->renderer = nullptr;
	this->width = lWidth;
	this->height = lHeight;
	this->windowTitle = lTitle;

	initialize();
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

void Window::initialize(){
	// Creates the SDL window.
	const Uint32 windowFlags = SDL_WINDOW_SHOWN;
	this->window = SDL_CreateWindow(this->windowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->width, this->height,
		windowFlags);
	if(this->window != nullptr){

		// Creates the SDL renderer.
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		if(this->renderer != nullptr){

			// Set texture filtering to linear.
			SDL_bool linearFilter = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			if(linearFilter){
				Logger::log("Linear texture filtering enabled!");
				rescale(192 * 5, 108 * 5);
			}
			else{
				Logger::warning("Linear texture filtering disabled!");
			}

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

void Window::rescale(unsigned int lWidth, unsigned int lHeight){
	// TODO: only set this if lWidth:lHeight matches the desired resolution, for example, 16:10.
	SDL_RenderSetLogicalSize(this->renderer, lWidth, lHeight);
}
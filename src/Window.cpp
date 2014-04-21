#include "Window.h"
#include "Logger.h"
#include "Configuration.h"

SDL_Renderer* Window::sdlRenderer = nullptr;

Window::Window(unsigned int width_, unsigned int height_, string title_) :
	width(width_),
	height(height_)	,
	windowTitle(title_),
	sdlWindow(nullptr)
{
	initialize();
}

Window::~Window(){
	destroy();
}

void Window::destroy(){
	// Destroys the Window renderer.
	SDL_DestroyRenderer(Window::sdlRenderer);
	Window::sdlRenderer = nullptr;

	// Destroys the Window window.
	SDL_DestroyWindow(this->sdlWindow);
	this->sdlWindow = nullptr;
}

void Window::minimize(){
	SDL_MinimizeWindow(this->sdlWindow);
}

void Window::maximize(){
	SDL_MaximizeWindow(this->sdlWindow);
}

void Window::clear(){
	SDL_SetRenderDrawColor(Window::sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(Window::sdlRenderer);
}

void Window::render(){
	SDL_RenderPresent(Window::sdlRenderer);
}

void Window::initialize(){
	// Creates the SDL window.
	const Uint32 windowFlags = SDL_WINDOW_SHOWN;
	this->sdlWindow = SDL_CreateWindow(
		this->windowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->width, this->height,
		windowFlags
	);
	
	if(this->sdlWindow != nullptr){

		// Creates the SDL renderer.
		Window::sdlRenderer = SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED);
		if(Window::sdlRenderer != nullptr){

			// Set texture filtering to linear.
			SDL_bool linearFilter = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			if(linearFilter){
				Logger::log("Linear texture filtering enabled!");
				rescale(5);
			}
			else{
				Logger::warning("Linear texture filtering disabled!");
			}

			Logger::verbose("Game successfully loaded.");
				
		}
		else{
			Logger::errorSDL("Renderer could not be created.", SDL_GetError());
		}
	}
	else{
		Logger::errorSDL("Window failed to be created.", SDL_GetError());
	}
}

void Window::rescale(unsigned int size_){
	// Just a precaution, so the the window size doesn't get huge.
	size_ = (size_ > 10) ? 10 : size_;
	SDL_RenderSetLogicalSize(Window::sdlRenderer, Configuration::resolutionWidth * size_, Configuration::resolutionHeight * size_);
}

SDL_Renderer* Window::getRenderer(){
	return Window::sdlRenderer;
}

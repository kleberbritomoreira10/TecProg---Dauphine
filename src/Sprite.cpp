#include "Sprite.h"
#include "Window.h"
#include "Logger.h"
#include <cassert>

Sprite::Sprite(const std::string& path_) :
	sdlTexture(nullptr),
	width(0),
	height(0),
	path(path_),
	animation(new Animation())
{
	loadFrom(this->path);
}

Sprite::~Sprite(){
	if(this->sdlTexture != nullptr){
		SDL_DestroyTexture(this->sdlTexture);
		this->sdlTexture = nullptr;
	}
}

void Sprite::loadFrom(const std::string& path_){
	assert(Window::getRenderer() != nullptr && "Window renderer should not be null!");

	// The final texture.
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path_.c_str());
	if(loadedSurface != nullptr){
		// Create texture from the surface pixels.
        newTexture = SDL_CreateTextureFromSurface(Window::getRenderer(), loadedSurface);
		if(newTexture != nullptr){
			// Set the Sprites width and height, from the loaded surface.
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
		}
		else{
			Logger::errorSDL("Could not create texture from surface.", SDL_GetError());
		}

		// Free the loaded surface.
		SDL_FreeSurface(loadedSurface);
	}
	else{
		Logger::errorSDL("Could not load surface from path.", IMG_GetError());
	}

	// Returns whether the Sprites texture is null or not.
	this->sdlTexture = newTexture;

	// Display error log if image wasn't loaded.
	if(this->sdlTexture == nullptr){
		Logger::error("Sprite load failed: " + path_);
	}
}

void Sprite::render(double x_, double y_, SDL_Rect* clip_, bool stretch_, double angle_, SDL_Point* center_,
	SDL_RendererFlip flip_){

	// This is the destination SDL_Rect structure.
	SDL_Rect renderQuad = {(int)x_, (int)y_, (int)this->width, (int)this->height};

	if(clip_ != nullptr){
		renderQuad.w = clip_->w;
		renderQuad.h = clip_->h;
	}
	else{

	}

	int successfullRender = (!stretch_) ?
		SDL_RenderCopyEx(Window::getRenderer(), this->sdlTexture, clip_,
			&renderQuad, angle_, center_, flip_) :
		SDL_RenderCopyEx(Window::getRenderer(), this->sdlTexture, clip_,
			nullptr, angle_, center_, flip_);
	
	if(successfullRender != 0){
		Logger::errorSDL("Failed to render sprite.", SDL_GetError());
	}
}

unsigned int Sprite::getWidth(){
	return this->width;
}

unsigned int Sprite::getHeight(){
	return this->height;
}

Animation& Sprite::getAnimation(){
	return (*(this->animation));
}

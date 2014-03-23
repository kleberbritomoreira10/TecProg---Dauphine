#include <iostream>
#include <string>
#include "DTexture.h"
#include "Logger.h"

using namespace std;

DTexture::DTexture(){
	this->sdlTexture = NULL;
	this->renderer = NULL;
	this->width = 0;
	this->height = 0;
}

DTexture::~DTexture(){
	free();
}

bool DTexture::loadFrom(string path, SDL_Renderer *renderer){
	free();
	this->renderer = renderer;

	// Final texture to be loaded.
	SDL_Texture *newTexture = NULL;

	// Load image at specified path.
	SDL_Surface *image = IMG_Load(path.c_str());
	if(image != NULL){
		// Color key image for magenta.
		//SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0xFF, 0, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(this->renderer, image);
		if(newTexture != NULL){
			this->width = image->w;
			this->height = image->h;
		}
		else{
			Logger::errorSDL("Could not create texture from image.", SDL_GetError());
		}

		SDL_FreeSurface(image);
	}
	else{
		Logger::errorSDL("Unable to load image from path.", IMG_GetError());
	}

	this->sdlTexture = newTexture;
	bool textureIsNotNull = (this->sdlTexture != NULL);
	return textureIsNotNull;
}

void DTexture::free(){
	if(this->sdlTexture != NULL){
		SDL_DestroyTexture(this->sdlTexture);
		this->sdlTexture = NULL;
		this->width = 0;
		this->height = 0;
		this->renderer = NULL;
	}
	else{
		// Do nothing.
	}
}

void DTexture::render(int x, int y, SDL_Rect *clip){
	SDL_Rect renderQuad = {x, y, this->width, this->height};

	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else{
		// Don't clip the texture.
	}

	if(this->renderer != NULL){
		SDL_RenderCopy(this->renderer, this->sdlTexture, clip, &renderQuad);
	}
	else{
		Logger::log("No renderer in DTexture.");
	}
}

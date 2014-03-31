#include "Sprite.h"
#include "Logger.h"

Sprite::Sprite(SDL_Renderer *lRenderer){
	this->width = 0;
	this->height = 0;
	this->sdlTexture = nullptr;
	this->sdlRenderer = lRenderer;

	if(this->sdlRenderer == nullptr){
		Logger::warning("Null renderer passed to Sprite. It will not be renderable.");	
	}
}

Sprite::~Sprite(){
	// Use the free() method to destroy everything but the renderer.
	free();

	// Just set the sdlRenderer to null. The Window class should delete or not the renderer.
	this->sdlRenderer = nullptr;
}

bool Sprite::loadFrom(string path){
	/// @todo Check if loading the texture via IMG_LoadTexture isn't better, and get width/height through the queryTexture method.

	// Warns if loading a sprite without a renderer.
	if(this->sdlRenderer == nullptr){
		Logger::warning("Trying to load sprite with null renderer.");
	}

	// Frees the texture if it already exists.
	free();

	// The final texture.
	SDL_Texture *newTexture = nullptr;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface != nullptr){
		//Color key image to magenta.
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));

		// Create texture from the surface pixels.
        newTexture = SDL_CreateTextureFromSurface(this->sdlRenderer, loadedSurface);
		if(newTexture != nullptr){
			// Set the Sprites width and height, from the loaded surface.
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
		}

		// Free the loaded surface.
		SDL_FreeSurface( loadedSurface );
	}

	// Returns whether the Sprites texture is null or not.
	this->sdlTexture = newTexture;
	return (this->sdlTexture != nullptr);
}

void Sprite::free(){
	// If the texture already exists, free it.
	if(this->sdlTexture != nullptr){
		SDL_DestroyTexture(this->sdlTexture);
		this->sdlTexture = nullptr;
		this->width = 0;
		this->height = 0;
	}
	else{
		// Do nothing.
	}
}

void Sprite::render(int x, int y, SDL_Rect *clip){
	SDL_Rect renderQuad = {(int)x, (int)y, (int)this->width, (int)this->height};

	if(clip != nullptr){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else{
		// Don't clip the texture.
	}

	SDL_RenderCopy(this->sdlRenderer, this->sdlTexture, clip, &renderQuad);
}

unsigned int Sprite::getWidth(){
	return this->width;
}

unsigned int Sprite::getHeight(){
	return this->height;
}

/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Animation.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

SDL_Window* sdlWindow = nullptr;
SDL_Renderer* sdlRenderer = nullptr;

SDL_Texture* sdlTexture = nullptr;
unsigned int width = 0;
unsigned int height = 0;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		const Uint32 windowFlags = SDL_WINDOW_SHOWN;
		sdlWindow = SDL_CreateWindow(
			"Teste", 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			windowFlags
		);

		if( sdlWindow == nullptr )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			printf("window created!\n");
		}
	}

	return success;
}

bool loadMedia()
{
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor( sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(sdlRenderer);

	// The final texture.
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load("res/nadineSprite.png");
	if(loadedSurface != nullptr){

        newTexture = SDL_CreateTextureFromSurface(sdlRenderer, loadedSurface);
		if(newTexture != nullptr){
			// Set the Sprites width and height, from the loaded surface.
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		else{
			printf("Could not create texture from surface.\n");
		}

		SDL_FreeSurface(loadedSurface);
	}
	else{
		printf("Could not load surface from path.\n");
	}

	sdlTexture = newTexture;

	// Returns whether the Sprites texture is null or not.
	// Display error log if image wasn't loaded.
	if(sdlTexture == nullptr){
		printf("Sprite load failed\n");
		return false;
	}
	else{
		return true;
	}

}

void close()
{
	SDL_DestroyTexture(sdlTexture);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			int lastdt = SDL_GetTicks();

		    Animation *animation = new Animation(0,0,229,229,11,false);
		    SDL_Rect *clip = new SDL_Rect();

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Indica quanto tempo, em ms, se passou desde ultimo frame
		        int dt = SDL_GetTicks() - lastdt;
		        lastdt = SDL_GetTicks();

				SDL_Rect renderQuad = {50, 50, 229, 229};

				animation->update(clip, dt, 200.0);

				SDL_RenderClear(sdlRenderer);

				int successfullRender = SDL_RenderCopyEx(sdlRenderer, sdlTexture, clip,
					&renderQuad, 0.0, nullptr, SDL_FLIP_NONE);
	
				if(successfullRender != 0){
					printf("Failed to render sprite. %s", SDL_GetError());
				}
			
				//Update the surface
				SDL_RenderPresent( sdlRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

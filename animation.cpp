/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* sdlWindow = nullptr;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

SDL_Renderer* sdlRenderer = nullptr;

//The image we will load and show on the screen
SDL_Surface* gXOut = nullptr;

unsigned int width;
unsigned int height;

SDL_Texture* sdlTexture;

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
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( sdlWindow );
		}
	}

	return success;
}

bool loadMedia()
{

	// Warns if loading a sprite without a renderer.
	if(sdlWindow == nullptr){
		printf("Trying to load sprite with null renderer.\n");
	}

	// The final texture.
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load("nadine.png");
	if(loadedSurface != nullptr){
		//Color key image to magenta.
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));
		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
		// Create texture from the surface pixels.
		if(sdlWindow == nullptr){
			printf("fodeu");
		}

        newTexture = SDL_CreateTextureFromSurface(sdlRenderer, loadedSurface);
		if(newTexture != nullptr){
			// Set the Sprites width and height, from the loaded surface.
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		else{
			printf("Could not create texture from surface.\n");
		}

		// Free the loaded surface.
		SDL_FreeSurface(loadedSurface);
	}
	else{
		printf("Could not load surface from path.\n");
	}

	// Returns whether the Sprites texture is null or not.
	sdlTexture = newTexture;

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

	//Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = nullptr;

	//Destroy window
	SDL_DestroyWindow( sdlWindow );
	sdlWindow = nullptr;

	//Destroy renderer
	SDL_DestroyRenderer(sdlRenderer);
	sdlRenderer = nullptr;

	//Destroy texture
	SDL_DestroyTexture(sdlTexture);
	sdlTexture = nullptr;

	//Quit SDL subsystems
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

				SDL_Rect renderQuad = {0, 0, 200, 200};

				int successfullRender = SDL_RenderCopyEx(sdlRenderer, sdlTexture, nullptr,
				&renderQuad, 0.0, nullptr, SDL_FLIP_NONE);
	
				if(successfullRender != 0){
					printf("Failed to render sprite. %s", SDL_GetError());
				}
			
				//Update the surface
				SDL_RenderPresent( sdlRenderer );

				//printf("%s", SDL_GetError());
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
#include <iostream>
#include <string>
#include "Game.h"
#include "Logger.h"

using namespace std;

Game::Game(){
	const int sdlInitialized = SDL_Init(SDL_INIT_EVERYTHING);
	if(sdlInitialized == 0){

		this->window = SDL_CreateWindow("Dauphine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		if(this->window != NULL){

			this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(this->renderer != NULL){

				int imgFlags = IMG_INIT_PNG;
				if(IMG_Init(imgFlags) & imgFlags){
					
					this->isRunning = true;

					DTexture dTexture;
					bool loadedTexture = dTexture.loadFrom("res/hdimg.png", this->renderer);
					if(loadedTexture){
						this->texture = dTexture;
					}
					else{
						Logger::error("Failed to load texture.");
					}
				}
				else{
					Logger::errorSDL("SDL_image could not be initialized.", IMG_GetError());
				}
			}
			else{
				Logger::errorSDL("Renderer could not be created.", SDL_GetError());
			}
		}
		else{
			Logger::errorSDL("Window failed to be created.", SDL_GetError());
		}
	}
	else{
		Logger::errorSDL("SDL failed to initialize.", SDL_GetError());
	}
}

Game::~Game(){
	this->texture.free();

	SDL_DestroyRenderer(this->renderer);
	this->renderer = NULL;

	SDL_DestroyWindow(this->window);
	this->window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Game::runGame(){
	while(this->isRunning){

		// Event handling.
		int pendingEvent = 0;
		do{
			pendingEvent = SDL_PollEvent(&this->eventHandler);
			switch(this->eventHandler.type){
				case SDL_QUIT:
					this->isRunning = false;
					break;
				case SDL_KEYDOWN:

					switch(this->eventHandler.key.keysym.sym){
						case SDLK_ESCAPE:
							this->isRunning = false;
						default:
							break;
					}

					break;
				default:
					break;
			}
		}while(pendingEvent != 0);

		// Set color and clear screen.
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render red quad.
		SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);

		// Render green outlined quad.
		SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &outlineRect);

		this->texture.render(0, 0);

		// Draw blue horizontal line.
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

		// Draw vertical line of yellow dots.
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		for(int i = 0; i < SCREEN_HEIGHT; i += 4){
			SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, i);
		}

		// Update screen.
		SDL_RenderPresent(renderer);
	}
}

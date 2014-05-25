#include "ControllerHandler.h"
#include "Logger.h"

#include <iostream>

ControllerHandler::ControllerHandler() :
    gameController(nullptr)
{

	if(SDL_NumJoysticks() > 0){
         this->gameController = SDL_GameControllerOpen(0);
 	}

	if(this->gameController == nullptr){
		Logger::warning("Unable to find a controller, defaulting to keyboard.");
    }

}

void ControllerHandler::handleInput(SDL_Event& sdlEvent_){
        
    SDL_Event fakeKeyInput;
        
    if(sdlEvent_.type == SDL_CONTROLLERBUTTONDOWN){

        fakeKeyInput.type = SDL_KEYDOWN;

        switch(sdlEvent_.cbutton.button){
            case controllerMap::buttons::FACE_DOWN: // Jump.
                fakeKeyInput.key.keysym.sym = SDLK_SPACE; 
                fakeKeyInput.key.state = SDL_PRESSED;
                break;
            
            case controllerMap::buttons::DLEFT: // Move Left.
                fakeKeyInput.key.keysym.sym = SDLK_LEFT; 
                fakeKeyInput.key.state = SDL_PRESSED;
                break;

            case controllerMap::buttons::DRIGHT: // Move Right.
                fakeKeyInput.key.keysym.sym = SDLK_RIGHT; 
                fakeKeyInput.key.state = SDL_PRESSED;
                break;

            case controllerMap::buttons::RDTRIGGER: // Roll
                fakeKeyInput.key.keysym.sym = SDLK_c; 
                fakeKeyInput.key.state = SDL_PRESSED;
                break;
            default:
                break;
        }

        SDL_PushEvent(&fakeKeyInput);
    }

    // On keyup.
    if(sdlEvent_.type == SDL_CONTROLLERBUTTONUP){

        fakeKeyInput.type = SDL_KEYUP;

        switch(sdlEvent_.cbutton.button){

            case controllerMap::buttons::FACE_DOWN: // Jump.
                fakeKeyInput.key.keysym.sym = SDLK_SPACE; 
                fakeKeyInput.key.state = SDL_RELEASED;
                break;
            
            case controllerMap::buttons::DLEFT: // Move Left.
                fakeKeyInput.key.keysym.sym = SDLK_LEFT; 
                fakeKeyInput.key.state = SDL_RELEASED;
                break;

            case controllerMap::buttons::DRIGHT: // Move Right.
                fakeKeyInput.key.keysym.sym = SDLK_RIGHT; 
                fakeKeyInput.key.state = SDL_RELEASED;
                break;

            case controllerMap::buttons::RDTRIGGER: // Roll
                fakeKeyInput.key.keysym.sym = SDLK_c; 
                fakeKeyInput.key.state = SDL_RELEASED;
                break;
            
            default:
                break;
        }

		SDL_PushEvent(&fakeKeyInput);
	}
	
	if(sdlEvent_.type == SDL_CONTROLLERAXISMOTION){

		std::cout << "Movement from axis " << (int)sdlEvent_.caxis.axis  << " with value" << sdlEvent_.caxis.value 	<< "\n";
			
		switch(sdlEvent_.caxis.axis){

			case controllerMap::axes::LATRIGGER:
					fakeKeyInput.key.keysym.sym = SDLK_DOWN; 
		
					if(sdlEvent_.caxis.value > TRIGGER_DEAD_ZONE){
						fakeKeyInput.type = SDL_KEYDOWN;
						fakeKeyInput.key.state = SDL_PRESSED;
					}

					else{
						fakeKeyInput.type = SDL_KEYUP;
						fakeKeyInput.key.state = SDL_RELEASED;
					}
					
				break;
				
			default:
				break;
		
		}

		SDL_PushEvent(&fakeKeyInput);

	}

}

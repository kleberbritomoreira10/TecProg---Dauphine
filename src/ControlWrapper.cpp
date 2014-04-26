#include "ControlWrapper.h"

ControlWrapper* ControlWrapper::instance = nullptr;

SDL_GameController* ControlWrapper::gameController = nullptr; /**< Pointer to the controller */

ControlWrapper::ControlWrapper(){

	if(SDL_NumJoysticks() > 0){
         gameController = SDL_GameControllerOpen(0);
 	}

	if(gameController == nullptr){
		Logger::log("Unable open Controller. Defaulting to Keyboard.");
    }

    return;
}

ControlWrapper* ControlWrapper::getInstance(){
    if(ControlWrapper::instance == nullptr){
        ControlWrapper::instance =  new ControlWrapper();
    }

    return ControlWrapper::instance;
}

void ControlWrapper::decide(){
    
    static SDL_Event eventHandler; /**< SDL internal event handler. */

    SDL_Event fakeKeyInput;

	int pendingEvent = 0;
    
    do{
        pendingEvent = SDL_PollEvent(&eventHandler); 
        
        if(eventHandler.type == SDL_CONTROLLERBUTTONDOWN){

            fakeKeyInput.type = SDL_KEYDOWN;

            switch(eventHandler.cbutton.button){
                case controller::buttons::FACE_DOWN: // Jump.

                    fakeKeyInput.key.keysym.sym = SDLK_SPACE; 
                    fakeKeyInput.key.state = SDL_PRESSED;
                
                break;
                
                case controller::buttons::DLEFT: // Move Left.

                    fakeKeyInput.key.keysym.sym = SDLK_LEFT; 
                    fakeKeyInput.key.state = SDL_PRESSED;
                
                break;

                case controller::buttons::DRIGHT: // Move Right.

                    fakeKeyInput.key.keysym.sym = SDLK_RIGHT; 
                    fakeKeyInput.key.state = SDL_PRESSED;
                
                break;

                case controller::buttons::RDTRIGGER: // Roll

                    fakeKeyInput.key.keysym.sym = SDLK_c; 
                    fakeKeyInput.key.state = SDL_PRESSED;
                
                break;

                default:
                
                break;
            }

            SDL_PushEvent(&fakeKeyInput);
        }

        // On keyup.
        if(eventHandler.type == SDL_CONTROLLERBUTTONUP){

            fakeKeyInput.type = SDL_KEYUP;

            switch(eventHandler.cbutton.button){

                case controller::buttons::FACE_DOWN: // Jump.

                    fakeKeyInput.key.keysym.sym = SDLK_SPACE; 
                    fakeKeyInput.key.state = SDL_RELEASED;
                
                break;
                
                case controller::buttons::DLEFT: // Move Left.

                    fakeKeyInput.key.keysym.sym = SDLK_LEFT; 
                    fakeKeyInput.key.state = SDL_RELEASED;
                
                break;

                case controller::buttons::DRIGHT: // Move Right.

                    fakeKeyInput.key.keysym.sym = SDLK_RIGHT; 
                    fakeKeyInput.key.state = SDL_RELEASED;
                
                break;

                case controller::buttons::RDTRIGGER: // Roll

                    fakeKeyInput.key.keysym.sym = SDLK_c; 
                    fakeKeyInput.key.state = SDL_RELEASED;
                
                break;
                
                default:
                
                break;
            
                SDL_PushEvent(&fakeKeyInput);
            }
        }
	} while(pendingEvent != 0);

	return;
}

#include "ControllerHandler.h"

ControllerHandler* ControllerHandler::instance = nullptr;

SDL_GameController* ControllerHandler::gameController = nullptr; /**< Pointer to the controllerMap */

ControllerHandler::ControllerHandler(){

	if(SDL_NumJoysticks() > 0){
         gameController = SDL_GameControllerOpen(0);
 	}

	if(gameController == nullptr){
		Logger::log("Unable open Controller. Defaulting to Keyboard.");
    }

    return;
}

ControllerHandler* ControllerHandler::getInstance(){
    if(ControllerHandler::instance == nullptr){
        ControllerHandler::instance =  new ControllerHandler();
    }

    return ControllerHandler::instance;
}

void ControllerHandler::handle(SDL_Event eventHandler){
    
    // static SDL_Event eventHandler; /**< SDL internal event handler. */

    SDL_Event fakeKeyInput;
        
    if(eventHandler.type == SDL_CONTROLLERBUTTONDOWN){

        fakeKeyInput.type = SDL_KEYDOWN;

        switch(eventHandler.cbutton.button){
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
    if(eventHandler.type == SDL_CONTROLLERBUTTONUP){

        fakeKeyInput.type = SDL_KEYUP;

        switch(eventHandler.cbutton.button){

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

	return;
}

#include "Player.h"
#include "InputHandler.h"
#include "Logger.h"
#include "Configuration.h"

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"

StatePlayer* Player::currentState = nullptr;
StatePlayer* Player::stateIdle = nullptr;
StatePlayer* Player::stateAerial = nullptr;
StatePlayer* Player::stateMoving = nullptr;
StatePlayer* Player::stateRolling = nullptr;
StatePlayer* Player::stateCrouching = nullptr;

Player::Player(double x_, double y_, Sprite* sprite_) :
    DynamicEntity(x_, y_, sprite_)
{

    Player::initializeStates();

	if(this->sprite != nullptr){
        Player::currentState = Player::stateIdle;
        Player::currentState->player = this;
        Player::currentState->enter();
	}
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    if(this->currentState != nullptr){
        this->currentState->exit();
    }

    Player::destroyStates();

    if(this->sprite != nullptr){
        delete this->sprite;
        this->sprite = nullptr;
    }
}

void Player::update(const double dt_){
    InputHandler* inputHandler = InputHandler::getInstance();
    array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    Player::currentState->handleInput(keyStates);
    updatePosition(dt_);
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy);
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    Player::stateIdle = new PStateIdle();
    Player::stateAerial = new PStateAerial();
    Player::stateMoving = new PStateMoving();
    Player::stateRolling = new PStateRolling();
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    delete Player::stateIdle;
    delete Player::stateAerial;
    delete Player::stateMoving;
    delete Player::stateRolling;
    //delete Player::stateCrouching;
}

void Player::changeState(StatePlayer& state_){
    Player* l_player = Player::currentState->player;
    
    Player::currentState->exit();
    Player::currentState = &state_;

    Player::currentState->player = l_player;
    Player::currentState->enter();
}


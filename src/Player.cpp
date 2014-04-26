#include "Player.h"
#include "InputHandler.h"
#include "Logger.h"
#include "Configuration.h"

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"

PlayerState* Player::currentAction = nullptr;
PlayerState* Player::actionIdle = nullptr;
PlayerState* Player::actionAerial = nullptr;
PlayerState* Player::actionMoving = nullptr;
PlayerState* Player::actionRolling = nullptr;
PlayerState* Player::actionCrouching = nullptr;

Player::Player(double x_, double y_, Sprite* sprite_) :
    DynamicEntity(x_, y_, sprite_)
{

    Player::initializeStates();

	if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();

        Player::currentAction = Player::actionIdle;
        Player::currentAction->player = this;
        Player::currentAction->enter();
	}
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    if(this->currentAction != nullptr){
        this->currentAction->exit();
    }

    Player::destroyStates();

    if(this->sprite != nullptr){
        this->sprite->free();
        delete this->sprite;
        this->sprite = nullptr;
    }
}

void Player::update(double dt_){
    InputHandler* inputHandler = InputHandler::getInstance();
    array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    Player::currentAction->handleInput(keyStates);
    updatePosition(dt_);
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy);
    }
}

void Player::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    Player::actionIdle = new PStateIdle();
    Player::actionAerial = new PStateAerial();
    Player::actionMoving = new PStateMoving();
    Player::actionRolling = new PStateRolling();
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    delete Player::actionIdle;
    delete Player::actionAerial;
    delete Player::actionMoving;
    delete Player::actionRolling;
    //delete Player::actionCrouching;
}

void Player::changeState(PlayerState& state_){
    Player* l_player = Player::currentAction->player;
    
    Player::currentAction->exit();
    Player::currentAction = &state_;

    Player::currentAction->player = l_player;
    Player::currentAction->enter();
}


#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"

Player::Player(double x_, double y_, Sprite* sprite_) :
    DynamicEntity(x_, y_, sprite_)
{

    initializeStates();

    if(this->sprite != nullptr){
        this->currentState = this->statesMap.at(IDLE);
        this->currentState->player = this;
        this->currentState->enter();
    }
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    if(this->currentState != nullptr){
        this->currentState->exit();
    }

    destroyStates();
}

void Player::update(const double dt_){
    std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

    Player::currentState->handleInput(keyStates);
    updatePosition(dt_);
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, &clip);
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    this->statesMap.emplace(IDLE, new PStateIdle());
    this->statesMap.emplace(MOVING, new PStateMoving());
    this->statesMap.emplace(AERIAL, new PStateAerial());
    this->statesMap.emplace(ROLLING, new PStateRolling());
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    std::map<PStates, StatePlayer*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
}

void Player::changeState(PStates state_){
    Player* l_player = this->currentState->player;
    
    this->currentState->exit();
    this->currentState = this->statesMap.at(state_);

    this->currentState->player = l_player;
    this->currentState->enter();
}


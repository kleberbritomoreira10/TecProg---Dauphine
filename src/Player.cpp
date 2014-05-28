#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "LuaScript.h"

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"

#include <iostream>

Player::Player(const double x_, const double y_, Sprite* const sprite_) :
    DynamicEntity(x_, y_, sprite_),
    animation(nullptr)
{

    initializeStates();

    LuaScript luaPlayer("lua/Player.lua");
    this->width = luaPlayer.unlua_get<int>("player.dimensions.width");
    this->height = luaPlayer.unlua_get<int>("player.dimensions.height");

    // Shouldn't be here.
    this->animation = new Animation(0, 3, this->width, this->height, 11, false);

    if(this->sprite != nullptr){
        this->currentState = this->statesMap.at(IDLE);
        this->currentState->enter();
    }
    else{
        Log(WARN) << "No sprite set for the player! Null sprite.";
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

    this->currentState->handleInput(keyStates);
    updatePosition(dt_);
    std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);
    this->animation->update(this->animationClip, dt_);
}

void Player::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
        if((int)this->y%64 > 0){
        	this->y += 64 -(int)this->y%64 + 1; 
        	this->vy = 0.0;
    	}
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
        if(this->currentState == this->statesMap.at(PStates::AERIAL)){
            this->y -= (int)(this->y + this->height)%64 - 1;
            this->vy = 0.0;
            changeState(PStates::IDLE);
        }
    }
    else{
        if(this->currentState != this->statesMap.at(PStates::AERIAL)){
            changeState(PStates::AERIAL);
        }
    }
    if(detections_.at(CollisionSide::SOLID_LEFT)){
        this->x -= (int)(this->x + this->width)%64 + 1;
        this->vx = 0.0;
    }
    if(detections_.at(CollisionSide::SOLID_RIGHT)){
    
//    	std::cout << (int)this->x%64 << "\n";
        if((int)this->x%64 > 0){
        	this->x += (64 - (int)this->x%64) + 1;
        	this->vx = 0.0;
        }
    }
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    this->statesMap.emplace(IDLE, new PStateIdle(this));
    this->statesMap.emplace(MOVING, new PStateMoving(this));
    this->statesMap.emplace(AERIAL, new PStateAerial(this));
    this->statesMap.emplace(ROLLING, new PStateRolling(this));
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    std::map<PStates, StatePlayer*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
}

void Player::changeState(const PStates state_){
    this->currentState->exit();
    this->currentState = this->statesMap.at(state_);
    this->currentState->enter();
}

Animation *Player::getAnimation(){
    return (this->animation);
}

bool Player::isCurrentState(const PStates state_){
    return (this->currentState == this->statesMap.at(state_));
}

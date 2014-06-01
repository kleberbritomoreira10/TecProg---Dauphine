#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "LuaScript.h"
#include <cmath>
#include <cfloat>

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"
#include "PStateCrouching.h"
#include "PStateAiming.h"
#include "PStateMovingCrouch.h"

Player::Player(const double x_, const double y_, Sprite* const sprite_) :
    DynamicEntity(x_, y_, sprite_),
    animation(nullptr),
    potionsLeft(3)
{

    initializeStates();

    LuaScript luaPlayer("lua/Player.lua");
    this->width = luaPlayer.unlua_get<int>("player.dimensions.width");
    this->height = luaPlayer.unlua_get<int>("player.dimensions.height");

    // Shouldn't be here?
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
    scoutPosition(dt_);

    const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

    updatePosition(dt_);

    this->animation->update(this->animationClip, dt_);

    for(auto potion : this->potions){
        potion->update(dt_);
    }
}

void Player::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    /// @todo Fix this magic 16, and the TOP collision.

    if(detections_.at(CollisionSide::SOLID_TOP)){ 
        //this->nextY += fmod(this->nextY, 64.0);
        this->vy = 0.0;
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
        if(isCurrentState(PStates::AERIAL)){ 
            this->nextY -= fmod(this->nextY, 64.0) - 16.0;
            this->vy = 0.0;
            changeState(PStates::IDLE);
        }
    }
    else{
        if(!isCurrentState(PStates::AERIAL)){
            changeState(PStates::AERIAL);
        }
    }
    if(detections_.at(CollisionSide::SOLID_LEFT)){
        this->nextX = this->x;
        this->vx = 0.0;
    }
    if(detections_.at(CollisionSide::SOLID_RIGHT)){
        this->nextX = this->x;
        this->vx = -0.001;
    }

}

void Player::render(const double cameraX_, const double cameraY_){
    
    const double dx = this->x - cameraX_;
    const double dy = this->y - cameraY_;
    if(this->sprite != nullptr){
        this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, getFlip());
    }

    for (auto potion : this->potions) {
        potion->getSprite()->render(potion->x - cameraX_, potion->y - cameraY_);
    }

}

void Player::usePotion(const int whichPotion, const int strength, const int distance){
    this->potions.at(whichPotion)->activated = true;
//    this->x = this->x + this->getWidth() - 20;

    if(this->isRight)
        this->potions.at(whichPotion)->x = this->x + this->getWidth() - this->potions.at(whichPotion)->getWidth();
    else
        this->potions.at(whichPotion)->x = this->x;
    
    this->potions.at(whichPotion)->y = this->y + 100;
    this->potions.at(whichPotion)->vx = 5;    
    this->potions.at(whichPotion)->vy = 5;
    
//    this->vy = (-1)*20;
    this->potions.at(whichPotion)->strength = strength;
    this->potions.at(whichPotion)->distance = distance;
    this->potions.at(whichPotion)->isRight = this->isRight;

    this->potions.at(whichPotion)->flightTime = 0;
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    this->statesMap.emplace(IDLE, new PStateIdle(this));
    this->statesMap.emplace(MOVING, new PStateMoving(this));
    this->statesMap.emplace(AERIAL, new PStateAerial(this));
    this->statesMap.emplace(ROLLING, new PStateRolling(this));
    this->statesMap.emplace(CROUCHING, new PStateCrouching(this));
    this->statesMap.emplace(AIMING, new PStateAiming(this));
    this->statesMap.emplace(MOVINGCROUCH, new PStateMovingCrouch(this));
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

Crosshair* Player::getCrosshair(){
    return crosshair;
}

void Player::setCrosshair(Crosshair* const crosshair_){
    this->crosshair = crosshair_;
}

Potion* Player::getPotion(){
    return potions[potions.size()];
}

void Player::setPotion(std::vector<Potion*> potions_){
    this->potions = potions_;
}

bool Player::isCurrentState(const PStates state_){
    return (this->currentState == this->statesMap.at(state_));
}

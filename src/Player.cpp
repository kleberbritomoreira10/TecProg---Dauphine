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

#include "Window.h"

#define ADD_STATE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))

#define FLOOR_OFFSET 8

Player::Player(const double x_, const double y_, const std::string& path_) :
    DynamicEntity(x_, y_, path_),
    potionsLeft(50),
    maxPotions(50),
    crosshair(new Crosshair(0.0, 0.0, "res/images/alvo.png")),
    animation(nullptr),
    currentState(nullptr)
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

    Game::instance().clearKeyFromInput(GameKeys::ACTION);

    scoutPosition(dt_);

    updateBoundingBox();

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
            const double magic = 0.0;
            const double aerialToIdleCorrection = 0.0;
            this->nextY -= fmod(this->nextY, 16.0) - magic + aerialToIdleCorrection;
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
    const double dy = this->y - cameraY_ + FLOOR_OFFSET;

    // // Actual.
    // SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &actualRect);

    // // Bounding box.
    // SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);

    if(this->sprite != nullptr){
        this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, getFlip());
    }

    if(this->crosshair != nullptr){
        this->crosshair->render(cameraX_, cameraY_);
    }

    for (auto potion : this->potions) {
        potion->render(cameraX_, cameraY_);
    }

}

void Player::usePotion(const int strength_, const int distance_){
    if(this->potionsLeft > 0){
        this->potionsLeft--;
        Potion* potion = new Potion( ((this->isRight) ? this->x + this->width : this->x), this->y, "res/images/potion.png", strength_, distance_, this->isRight);
        potion->activated = true;
        this->potions.push_back(potion);
    }
}

void Player::addPotions(const unsigned int quantity_){
    if(this->potionsLeft + quantity_ > this->maxPotions){
        this->potionsLeft = this->maxPotions;
    }
    else{
        this->potionsLeft += quantity_;
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    ADD_STATE(IDLE,         PStateIdle);
    ADD_STATE(MOVING,       PStateMoving);
    ADD_STATE(AERIAL,       PStateAerial);
    ADD_STATE(ROLLING,      PStateRolling);
    ADD_STATE(CROUCHING,    PStateCrouching);
    ADD_STATE(AIMING,       PStateAiming);
    ADD_STATE(MOVINGCROUCH, PStateMovingCrouch);
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


void Player::updateBoundingBox(){
    this->boundingBox.x = (int) this->nextX + this->currentState->box.x;
    this->boundingBox.y = (int) this->nextY + this->currentState->box.y;
    this->boundingBox.w = (int) this->width - this->currentState->box.w;
    this->boundingBox.h = (int) this->height - this->currentState->box.h;
}


#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "LuaScript.h"

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"
#include "PStateAiming.h"
Player::Player(const double x_, const double y_, Sprite* const sprite_) :
    DynamicEntity(x_, y_, sprite_),
    animation(nullptr)
{

    initializeStates();

    LuaScript luaPlayer("lua/Level1.lua");
    this->width = luaPlayer.unlua_get<int>("level.player.width");
    this->height = luaPlayer.unlua_get<int>("level.player.height");

    // Shouldn't be here.
    this->animation = new Animation(0, 3, this->width, this->height, 11, false);

    if(this->sprite != nullptr){
        this->currentState = this->statesMap.at(IDLE);
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

    this->currentState->handleInput(keyStates);
    updatePosition(dt_);
    this->animation->update(this->clip, dt_);
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy, &clip, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    this->statesMap.emplace(IDLE, new PStateIdle(this));
    this->statesMap.emplace(MOVING, new PStateMoving(this));
    this->statesMap.emplace(AERIAL, new PStateAerial(this));
    this->statesMap.emplace(ROLLING, new PStateRolling(this));
    this->statesMap.emplace(AIMING, new PStateAiming(this));
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

Crosshair* Player::getCrosshair()
{
    return crosshair;
}

void Player::setCrosshair(Crosshair* crosshair)
{
    this->crosshair = crosshair;
}

BombPotion* Player::getBombPotion()
{
    return bombPotion;
}

void Player::setBombPotion(BombPotion* bombPotion)
{
    this->bombPotion = bombPotion;
}

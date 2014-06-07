#include "Enemy.h"
#include "Logger.h"
#include <cmath>

#include "EStateIdle.h"
#include "EStatePatrolling.h"
#include "EStateAerial.h"
#include "EStateCurious.h"
#include "EStateAlert.h"
#include "EStateAtack.h"

#include "Window.h"

#define ADD_STATE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))

double Enemy::px = 0.0;
double Enemy::py = 0.0;
unsigned int Enemy::pLife = 3;
double Enemy::alertRange = 300.0;
double Enemy::curiousRange = 600.0;

Enemy::Enemy(const double x_, const double y_, const std::string& path_, const bool patrol_,
    const double patrolLength_) :

	DynamicEntity(x_, y_, path_),
    originalX(x_),
    patrol(patrol_),
    patrolLength(patrolLength_),
	currentState(nullptr),
	statesMap()
{
	initializeStates();

    this->speed = 3.0;

    this->currentState = this->statesMap.at(PATROLLING);
    this->currentState->enter();
}

Enemy::~Enemy(){
	if(this->currentState != nullptr){
        this->currentState->exit();
    }

    destroyStates();
}

void Enemy::update(const double dt_){
    this->currentState->update(dt_);
    forceMaxSpeed();

    scoutPosition(dt_);

    this->boundingBox = {(int)this->nextX + (int)this->width/4, (int)this->nextY + 70, (int)this->width/2, (int)this->height - 70};

    const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

    updatePosition(dt_);

}

void Enemy::render(const double cameraX_, const double cameraY_){

    const double dx = this->x - cameraX_;
    const double dy = this->y - cameraY_;

    // Actual.
    SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
    SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(Window::getRenderer(), &actualRect);

    // Bounding box.
    SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
    SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);

    if(this->sprite != nullptr){

        //                           &this->animationClip
        this->sprite->render(dx, dy, nullptr, false, 0.0, nullptr, getFlip());
    }
}

void Enemy::initializeStates(){
    // Initialize all the states in Enemy here.
    ADD_STATE(IDLE, EStateIdle);
    ADD_STATE(CURIOUS, EStateCurious);
    ADD_STATE(PATROLLING, EStatePatrolling);
    ADD_STATE(ALERT, EStateAlert);
    ADD_STATE(AERIAL, EStateAerial);
    ADD_STATE(ATACK, EStateAtack);
}

void Enemy::destroyStates(){
	// Delete all the states in Enemy here.
    std::map<EStates, StateEnemy*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
}

void Enemy::changeState(const EStates state_){
    this->currentState->exit();
    this->currentState = this->statesMap.at(state_);
    this->currentState->enter();
}

void Enemy::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
        this->vy = 0.0;
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
        if(this->currentState == this->statesMap.at(EStates::AERIAL)){
            this->nextY -= fmod(this->nextY, 64.0) - 16.0;
            this->vy = 0.0;
            changeState(EStates::PATROLLING);
        }
    }
    else{
        if(this->currentState != this->statesMap.at(EStates::AERIAL)){
            changeState(EStates::AERIAL);
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

void Enemy::forceMaxSpeed(){
    this->vx = (this->vx >= this->maxSpeed) ? this->maxSpeed : this->vx ;
    this->vy = (this->vy >= this->maxSpeed) ? this->maxSpeed : this->vy ;
}

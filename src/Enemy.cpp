#include "Enemy.h"

#include "EStateIdle.h"
#include "EStateMoving.h"
#include "EStateAerial.h"

double Enemy::px = 0.0;
double Enemy::py = 0.0;

Enemy::Enemy(const double x_, const double y_, Sprite* const sprite_) :
	DynamicEntity(x_, y_, sprite_),
    patrolX(100.0),
    left(true),
	currentState(nullptr),
	statesMap()
{
	initializeStates();

    this->currentState = this->statesMap.at(IDLE);
    this->currentState->enter();
}

Enemy::~Enemy(){
	if(this->currentState != nullptr){
        this->currentState->exit();
    }

    destroyStates();
}

void Enemy::update(const double dt_){
    this->currentState->update();
    updatePosition(dt_);
}

void Enemy::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy);
    }
}

void Enemy::initializeStates(){
    // Initialize all the states in Enemy here.
    this->statesMap.emplace(IDLE, new EStateIdle(this));
    this->statesMap.emplace(MOVING, new EStateMoving(this));
    this->statesMap.emplace(AERIAL, new EStateAerial(this));
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

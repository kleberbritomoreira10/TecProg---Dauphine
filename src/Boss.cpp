#include "Boss.h"
#include "Logger.h"
#include <cmath>

#include "BStateIdle.h"
#include "BStateAttack.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<BStates, StateBoss*>(stateEnum, new stateClass(this)));

Boss::Boss(const double x_, const double y_, const std::string& path_) :
	DynamicEntity(x_, y_, path_),	
	potionsLeft(3),
	sawPlayer(false),
	potions(),
	currentState(nullptr),
	animation(nullptr),
	statesMap(),
	dead(false)
{
	initializeStates();

	this->isRight = true;

	this->speed = 400.0;

	this->width = 360;
	this->height = 240;

	this->animation = new Animation(0, 0, this->width, this->height, 0, false);
	this->currentState = this->statesMap.at(IDLE);
	this->currentState->enter();
}

Boss::~Boss(){
	if(this->currentState != nullptr){
		this->currentState->exit();
	}

	destroyStates();
}

void Boss::update(const double dt_){
	
	scoutPosition(dt_);

	this->animation->update(this->animationClip, dt_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(dt_);

	this->currentState->update(dt_);

    for(auto potion : this->potions){
        if(!potion->activated){
            // Delete potion.
        }
        potion->update(dt_);
    }
}

void Boss::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;

	/////////////////////////////////////////////////////////////////////////////////////////
	// //Actual.
	// SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &actualRect);

	// //Bounding box.
	// SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
	///////////////////////////////////////////////////////////////////////////////////////////

	if(this->sprite != nullptr){
		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL){
			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);
		}
		else{
			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
		}
	}

    for (auto potion : this->potions) {
        potion->render(cameraX_, cameraY_);
    }
}

void Boss::initializeStates(){
	// Initialize all the states in Boss here.
	ADD_STATE_INSERT(IDLE,		BStateIdle);
	ADD_STATE_INSERT(ATTACK,	BStateAttack);
}

void Boss::destroyStates(){
	// Delete all the states in Boss here.
	std::map<BStates, StateBoss*>::const_iterator it;
	for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
		delete it->second;
	}
}

void Boss::changeState(const BStates state_){
	this->currentState->exit();
	this->currentState = this->statesMap.at(state_);
	this->currentState->enter();
}

void Boss::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
	if(detections_.at(CollisionSide::SOLID_TOP)){ 
		this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_BOTTOM)){		
			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;
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

void Boss::usePotion(const int strength_, const int distance_){
    if(this->potionsLeft > 0){
        this->potionsLeft--;
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);
        Potion* potion = new Potion(potionX , this->y, "res/images/potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);
    }
}

Animation *Boss::getAnimation(){
	return (this->animation);
}

void Boss::setDead(bool isDead_){
	this->dead = isDead_;
}

bool Boss::isDead(){
	return this->dead;
}

void Boss::updateBoundingBox(){
	this->boundingBox.x = (int) this->nextX + 40;
	this->boundingBox.y = (int) this->nextY + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;
}

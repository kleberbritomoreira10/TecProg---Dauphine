#include "Enemy.h"
#include "Logger.h"
#include "LuaScript.h"
#include <cmath>
#include "EStateIdle.h"
#include "EStatePatrolling.h"
#include "EStateAerial.h"
#include "EStateCurious.h"
#include "EStateAlert.h"
#include "EStateAttack.h"
#include "EStateDead.h"
#include "Window.h"

#define ADD_STATE_EMPLACE(state_enum, state_class) this->states_map.emplace(state_enum, new state_class(this))
#define ADD_STATE_INSERT(state_enum, state_class) this->states_map.insert(std::make_pair<EStates, StateEnemy*>(state_enum, new state_class(this)));

double Enemy::x_position = 0.0;
double Enemy::y_position = 0.0;
unsigned int Enemy::life_points = 3;
bool Enemy::vulnerable = false;
double Enemy::alert_range = 300.0;
double Enemy::curious_range = 600.0;

Enemy::Enemy(const double x_, const double y_, const std::string& path_, const bool patrol_, 
	const double patrol_length_) : 
  DynamicEntity(x_, y_, path_),
	originalX(x_),
	patrol(patrol_),
	patrolLength(patrol_length_),
	life(100),
	current_state(nullptr),
	animation(nullptr),
	states_map(),
	dead(false)
{
	initializeStates();

	this->speed = 3.0;
	LuaScript luaEnemy("lua/Enemy.lua");
	this->width = luaEnemy.unlua_get<int>("enemy.dimensions.width");
	this->height = luaEnemy.unlua_get<int>("enemy.dimensions.height");
	this->animation = new Animation(0, 0, this->width, this->height, 0, false);

	if(this->patrol)
	{
		this->current_state = this->states_map.at(PATROLLING);
	}
	else 
	{
		this->current_state = this->states_map.at(IDLE);
	}
	
	this->current_state->enter();
}

Enemy::~Enemy()
{
	if(this->current_state != nullptr)
	{
		this->current_state->exit();
		this->current_state = nullptr;
	}

	if(this->animation != nullptr)
	{
    delete this->animation;
    this->animation = nullptr;
  }

	destroyStates();
}

void Enemy::update(const double dt_)
{
	this->current_state->update(dt_);
	forceMaxSpeed();

	scoutPosition(dt_);

	this->animation->update(this->animationClip, dt_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(dt_);
}

void Enemy::render(const double cameraX_, const double cameraY_)
{
	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;
	///////////////////////////////////////////////////////////////////////////////////////////
	// // Actual.
	// SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &actualRect);

	// Bounding box.
	// SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
	// ///////////////////////////////////////////////////////////////////////////////////////////

	if(this->sprite != nullptr)
	{
		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL)
		{
			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);
		}	else
		  {
			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
		  }
	}
}

void Enemy::initializeStates()
{
	// Initialize all the states in Enemy here.
	ADD_STATE_INSERT(IDLE,         EStateIdle);
	ADD_STATE_INSERT(CURIOUS,      EStateCurious);
	ADD_STATE_INSERT(PATROLLING,   EStatePatrolling);
	ADD_STATE_INSERT(ALERT,        EStateAlert);
	ADD_STATE_INSERT(AERIAL,       EStateAerial);
	ADD_STATE_INSERT(ATTACK,       EStateAttack);
	ADD_STATE_INSERT(DEAD,         EStateDead);
}

void Enemy::destroyStates()
{
	// Delete all the states in Enemy here.
	std::map<EStates, StateEnemy*>::const_iterator it;
	for(it = this->states_map.begin(); it != this->states_map.end(); it++)
	{
		delete it->second;
	}
}

void Enemy::changeState(const EStates state_)
{
	this->current_state->exit();
	this->current_state = this->states_map.at(state_);
	this->current_state->enter();
}

void Enemy::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_)
{
	if(detections_.at(CollisionSide::SOLID_TOP))
	{ 
		this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_BOTTOM))
	{
		if(this->current_state == this->states_map.at(EStates::AERIAL) || this->current_state == this->states_map.at(EStates::DEAD))
		{
			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;
			if(this->isDead())
			{
				this->changeState(EStates::DEAD);
			}
			if(this->patrol)
			{
				this->changeState(EStates::PATROLLING);
			} else
			  {
				  this->changeState(EStates::IDLE);
				  return;
			  }
		  }
	} else 
	  {
		  if(this->current_state != this->states_map.at(EStates::AERIAL)){
			  changeState(EStates::AERIAL);
		  }
	  }
	if(detections_.at(CollisionSide::SOLID_LEFT))
	{
		this->nextX = this->x;
		this->vx = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_RIGHT))
	{
		this->nextX = this->x;
		this->vx = -0.001;
	}
}

void Enemy::forceMaxSpeed()
{
	this->vx = (this->vx >= this->maxSpeed) ? this->maxSpeed : this->vx ;
	this->vy = (this->vy >= this->maxSpeed) ? this->maxSpeed : this->vy ;
}

Animation *Enemy::getAnimation()
{
	return (this->animation);
}

void Enemy::setDead(bool isDead_)
{
	this->dead = isDead_;
}

bool Enemy::isDead()
{
	return this->dead;
}

void Enemy::updateBoundingBox()
{
	this->boundingBox.x = (int) this->nextX + 40;
	this->boundingBox.y = (int) this->nextY + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;
}

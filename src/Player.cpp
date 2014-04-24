#include "Player.h"
#include "InputHandler.h"
#include "Logger.h"
#include "Configuration.h"

#include "ActionIdle.h"
#include "ActionAerial.h"
#include "ActionMoving.h"

Action* Player::currentAction = nullptr;
Action* Player::actionIdle = nullptr;
Action* Player::actionAerial = nullptr;
Action* Player::actionMoving = nullptr;
Action* Player::actionRolling = nullptr;
Action* Player::actionCrouching = nullptr;

Player::Player(double x_, double y_, Sprite* sprite_) :
    Entity(x_, y_, sprite_),
    vx(0),
    vy(0),
    speed(15),
    maxSpeed(500),
    isGrounded(false),
    levelW(0),
    levelH(0)
{

    Player::initializeStates();

	if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();

        Player::currentAction = Player::actionIdle;
        Player::currentAction->setPlayer(this);
        Player::currentAction->load();
	}
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    if(this->currentAction != nullptr){
        this->currentAction->unload();
    }

    Player::destroyStates();

    if(this->sprite != nullptr){
        this->sprite->free();
        delete this->sprite;
        this->sprite = nullptr;
    }
}

void Player::update(double dt_){
    Player::currentAction->update(dt_);
    updatePosition(dt_);
}

void Player::render(const double cameraX_, const double cameraY_){
    if(this->sprite != nullptr){
        const double dx = this->x - cameraX_;
        const double dy = this->y - cameraY_;
        this->sprite->render(dx, dy);
    }
}

void Player::updatePosition(double dt_){
    /// @todo Fix all these magic/weird numbers.
    this->x += this->vx * dt_;

    // Left wall.
    if(this->x < 0){
        this->x = 0;
        this->vx = 0;
    }
    // Right wall.
    else if(this->x + this->width > this->levelW){
        this->x = this->levelW - this->width;
        this->vx = 0;
    }

    this->y += this->vy * dt_;

    // Top wall.
    if(this->y < 0){
        this->y = 0;
        this->vy = 0;
    }
    // Bottom wall.
    else if(this->y + this->height >= this->levelH){
        this->y = this->levelH - this->height;
        this->vy = 0;
        this->isGrounded = true;
    }
    else{
        this->isGrounded = false;
    }

}

/*
    switch(this->state){
        case STATE_STANDING:

            if(keyStates[GameKeys::ROLL]){
                 this->state = STATE_ROLLING;
            }
            if(keyStates[GameKeys::DOWN]){
                this->speed = 7.5;
                this->maxSpeed = 350;
                this->state = STATE_CROUCHING;
            }
            break;

        case STATE_CROUCHING:
            if(!keyStates[GameKeys::DOWN]){
                this->speed = 15;
                this->maxSpeed = 500;
                this->state = STATE_STANDING;
            }
            break;

        case STATE_ROLLING:
            this->vx = 70*this->speed;
            this->state = STATE_STANDING;
            break;
*/

void Player::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    Player::actionIdle = new ActionIdle();
    Player::actionAerial = new ActionAerial();
    Player::actionMoving = new ActionMoving();
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    delete Player::actionIdle;
    delete Player::actionAerial;
    delete Player::actionMoving;
    //delete Player::actionRolling;
    //delete Player::actionCrouching;
}

void Player::setAction(Action& action_){
    Player* player = Player::currentAction->getPlayer();
    
    Player::currentAction->unload();
    Player::currentAction = &action_;

    Player::currentAction->setPlayer(player);
    Player::currentAction->load();
}

void Player::jump(){
    this->vy = (-40) * this->speed;
}

void Player::applyGravity(){
    this->vy += 2 * this->speed;
}

void Player::move(bool movingLeft_, bool movingRight_){
    if(movingLeft_ || movingRight_){
        if(movingLeft_){
            this->vx -= this->speed;
            this->vx = (this->vx < -this->maxSpeed) ? -this->maxSpeed : this->vx;
        }
        if(movingRight_){
            this->vx += this->speed;
            this->vx = (this->vx > this->maxSpeed) ? this->maxSpeed : this->vx;
        }
    }
    else{
        slowVx();
    }
    
}

void Player::slowVx(){
    this->vx *= 0.8;
}

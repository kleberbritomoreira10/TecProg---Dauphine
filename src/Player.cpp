#include "Player.h"
#include "InputHandler.h"
#include "Logger.h"
#include "Configuration.h"

#include "ActionStanding.h"
#include "ActionAerial.h"
#include "ActionWalking.h"

Action* Player::currentAction = nullptr;
Action* Player::actionStanding = nullptr;
Action* Player::actionAerial = nullptr;
Action* Player::actionWalking = nullptr;

Player::Player(double x_, double y_, Sprite* sprite_) :
    Entity(x_, y_, sprite_),
    vx(0),
    vy(0),
    speed(15),
    maxSpeed(500),
    levelW(0),
    levelH(0)
{

    Player::initializeStates();

	if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();

        Player::currentAction = Player::actionAerial;
        Player::currentAction->setPlayer(this);
        Player::currentAction->load();
	}
    else{
        Logger::warning("No sprite set for the player! Null sprite.");
    }
}

Player::~Player(){
    if(this->sprite != nullptr){
        this->sprite->free();
        delete this->sprite;
        this->sprite = nullptr;
    }
}

void Player::update(double dt_){
    //updateInput();
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
    else if(this->y + this->height + 40 > this->levelH){
        this->y = this->levelH - this->height - 40;
        this->vy = 0;
        Player::setAction((*Player::actionStanding));
    }
}

void Player::updateInput(){
    InputHandler* inputHandler = InputHandler::getInstance();
    const array<bool, GameKeys::MAX> keyStates = inputHandler->getKeyStates();

    /// @todo Fix all these magic/weird numbers.
    /*switch(this->state){
        case STATE_STANDING:
            if(keyStates[GameKeys::UP]){
                this->state = STATE_JUMPING;
                this->vy = -40*this->speed;
            }
            if(keyStates[GameKeys::ROLL]){
                 this->state = STATE_ROLLING;
            }
            if(keyStates[GameKeys::DOWN]){
                this->speed = 7.5;
                this->maxSpeed = 350;
                this->state = STATE_CROUCHING;
            }
            break;

        case STATE_JUMPING:
            this->vy += 2*this->speed;
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

        default:
            break;
    }*/

}

void Player::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    Player::actionStanding = new ActionStanding();
    Player::actionAerial = new ActionAerial();
    Player::actionWalking = new ActionWalking();
}

void Player::setAction(Action& action_){
    Player* player = Player::currentAction->getPlayer();
    
    Player::currentAction->unload();
    Player::currentAction = &action_;

    Player::currentAction->setPlayer(player);
    Player::currentAction->load();
}


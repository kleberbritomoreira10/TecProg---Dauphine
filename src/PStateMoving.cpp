#include "PStateMoving.h"
#include "Logger.h"

void PStateMoving::enter(){
    Logger::verbose("enter-> MOVING");
}

void PStateMoving::exit(){

}

void PStateMoving::handleInput(const array<bool, GameKeys::MAX> keyStates_){
    // Aerial
    if(!this->player->isGrounded){
        this->player->changeState((*Player::actionAerial));
        return;     
    }

    // Jump
    if(keyStates_[GameKeys::UP] && this->player->isGrounded){
        this->player->jump();
        this->player->changeState((*Player::actionAerial));
        return;
    }

    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

    if(keyStates_[GameKeys::ROLL]){
        this->player->changeState((*Player::actionRolling));
        return;
    }

    // Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState((*Player::actionIdle));
        return;
    }
}

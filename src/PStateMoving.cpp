#include "PStateMoving.h"
#include "Logger.h"

void PStateMoving::enter(){

}

void PStateMoving::exit(){

}

void PStateMoving::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
    // Aerial
    if(!this->player->isGrounded){
        this->player->changeState((*Player::stateAerial));
        return;     
    }

    // Jump
    if(keyStates_[GameKeys::UP] && this->player->isGrounded){
        this->player->jump();
        this->player->changeState((*Player::stateAerial));
        return;
    }

    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

    if(keyStates_[GameKeys::ROLL]){
        this->player->changeState((*Player::stateRolling));
        return;
    }

    // Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState((*Player::stateIdle));
        return;
    }
}

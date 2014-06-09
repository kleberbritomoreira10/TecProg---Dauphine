#include "PStateMoving.h"
#include "Logger.h"

#define THROW_STRENGTH 30
#define THROW_DISTANCE 150

void PStateMoving::enter(){
    this->box.x = (int)this->player->getWidth() / 4 - 33;
    this->box.y = (int)this->player->getHeight() / 3.5;
    this->box.w = (int)this->player->getWidth() / 1.7;
    this->box.h = (int)this->player->getHeight() / 3.5;

    this->player->getAnimation()->changeAnimation(4,2,9,false,0.9);
}

void PStateMoving::exit(){

}

void PStateMoving::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
    // Aerial
    if(!this->player->isGrounded){
        this->player->changeState(Player::PStates::AERIAL);
        return;     
    }

    // Jump
    if(keyStates_[GameKeys::SPACE] && this->player->isGrounded){
        this->player->jump();
        this->player->isGrounded = false;
        return;
    }

    if(keyStates_[GameKeys::ACTION]){
        if(this->player->potionsLeft > 0){  
            this->player->usePotion(THROW_STRENGTH, THROW_DISTANCE);
            this->player->potionsLeft--;
            return;
        }
    }

    // Crouch
    if(keyStates_[GameKeys::CROUCH]){
        this->player->changeState(Player::PStates::CROUCHING);
        return;
    }

    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

    if(keyStates_[GameKeys::ROLL]){
        this->player->changeState(Player::PStates::ROLLING);
        return;
    }

    // Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState(Player::PStates::IDLE);
        return;
    }
}

PStateMoving::PStateMoving(Player* const player_) :
    StatePlayer(player_)
{

}

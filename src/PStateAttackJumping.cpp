#include "PStateAttackJumping.h"
#include "Logger.h"
#include "Game.h"

void PStateAttackJumping::enter(){

   	this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

    this->player->getAnimation()->changeAnimation(3, 9, 7, false, 0.4);

    Game::instance().getAudioHandler().addSoundEffect("res/audio/FX_NADINE/FX_SUPERAAAH.wav");
}

void PStateAttackJumping::exit(){
	Log(DEBUG) << "EXIT STATE ATTACK JUMPING";
}

void PStateAttackJumping::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	Log(DEBUG) << "STATE ATTACK JUMPING";

	if(this->player->getAnimation()->getCurrentFrame() == 7){
		this->player->changeState(Player::PStates::AERIAL);
	}
	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

PStateAttackJumping::PStateAttackJumping(Player* const player_) :
	StatePlayer(player_)
{

}

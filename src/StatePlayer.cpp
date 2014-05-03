#include "StatePlayer.h"

StatePlayer::StatePlayer(Player* const player_) :
	player(player_)
{

}

StatePlayer::~StatePlayer(){
	this->player = nullptr;
}

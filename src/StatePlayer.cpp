#include "StatePlayer.h"

StatePlayer::StatePlayer(Player* player_) :
	player(player_)
{

}

StatePlayer::~StatePlayer(){
	this->player = nullptr;
}

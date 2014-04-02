#include "Command.h"

Command::Command(Player *player, Method method){
    this->player_ = player;
    this->method_ = method;
}

void Command::execute(){
	(this->player_->*method_)();
}

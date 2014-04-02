#ifndef INCLUDE_COMMAND_H
#define INCLUDE_COMMAND_H

#include "Player.h"

class Command {

	typedef void (Player:: *Method)();

	public:
		Command(Player *player, Method method);
		void execute();

	private:
		Player *player_;
		Method method_;

};

#endif //INCLUDE_COMMAND_H
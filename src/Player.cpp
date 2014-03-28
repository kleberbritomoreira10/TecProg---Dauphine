#include "Sprite.h"
#include "Game.h"

Player::Player(double x, double y, Game *lgame){
	this->x = x;
	this->y = y;
	this->game = lgame;
}

void Player::render(){
	Sprite *sprite = nullptr;
	sprite = new Sprite(this->game->gameWindow->renderer);
	bool loadedSprite = sprite->loadFrom("res/Player.png");
	if(!loadedSprite){
		Logger::error("Couldn't load sprite.");
	}

	sprite->render(this->x, this->y, nullptr);
}
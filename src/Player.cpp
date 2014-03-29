#include "Player.h"
#include "Logger.h"

Player::Player(double lX, double lY, Sprite *lSprite){
	this->x = lX;
	this->y = lY;
	this->sprite = lSprite;

	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the player! Null sprite.");
	}
}

Player::~Player(){
	this->x = 0;
	this->y = 0;

	delete this->sprite;
	this->sprite = nullptr;
}

void Player::update(double dt){
	//TODO: everything, I guess
	this->x += 0.1;
}

void Player::render(){
	this->sprite->render(this->x, this->y, nullptr);
}

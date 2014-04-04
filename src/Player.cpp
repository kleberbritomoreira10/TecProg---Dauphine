#include "Player.h"
#include "Logger.h"

const int SCREEN_WIDTH = 192 * 5;
const int SCREEN_HEIGHT = 108 * 5;

Player::Player(int lX, int lY, Sprite *lSprite){
	this->x = lX;
	this->y = lY;
    this->vx = 0;
    this->vy = 0;
    this->speed = 2.5;

	this->sprite = lSprite;

	if(this->sprite == nullptr){
		Logger::warning("No sprite set for the player! Null sprite.");
	}
}

Player::~Player(){
	this->x = 0;
	this->y = 0;
    this->vx = 0;
    this->vy = 0;

	/// @todo: Maybe this isn't the best place to delete the Sprite object.
	delete this->sprite;
	this->sprite = nullptr;
}

void Player::update(double dt, bool keyState[10]){
	/// @todo: Implement everything in this method, pretty much.
    if(keyState[0]){
    	this->vy -= 10;
    }
    else{
 		if(this->y >= (SCREEN_HEIGHT - 100)){
    		this->y = SCREEN_HEIGHT - 99;
    		this->vy = 0;
		}
		else{
			this->vy += 10;
		}
    }

	if(keyState[1]){
    	this->vx -= 10;
    }
    else if(keyState[2]){
    	this->vx += 10;
    }
    else{
    	this->vx *= 0.98;
    }
   

    this->x += this->vx * dt;
    this->y += this->vy * dt;

}

void Player::render(){
	this->sprite->render(this->x, this->y, nullptr);
}

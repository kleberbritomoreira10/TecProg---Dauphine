#include "Player.h"
#include "Logger.h"

const int SCREEN_WIDTH = 192 * 5;
const int SCREEN_HEIGHT = 108 * 5;

Player::Player(int lX, int lY, Sprite *lSprite){
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

	/// @todo: Maybe this isn't the best place to delete the Sprite object.
	delete this->sprite;
	this->sprite = nullptr;
}

void Player::update(double dt, int velX, int velY){
	/// @todo: Implement everything in this method, pretty much.
 	//Move the player left or right.
    this->x += velX;

    // If the player went too far to the left or right.
    if( ( this->x < 0 ) || ( this->x + this->sprite->width > SCREEN_WIDTH ) )
    {
        //Move back.
        this->x -= velX;
    }

    // Move the player up or down.
    this->y += velY;

    // If the player went too far up or down.
    if( ( this->y < 0 ) || ( this->y + this->sprite->height > SCREEN_HEIGHT ) )
    {
        // Move back.
        this->y -= velY;
    }
}

void Player::render(){
	this->sprite->render(this->x, this->y, nullptr);
}

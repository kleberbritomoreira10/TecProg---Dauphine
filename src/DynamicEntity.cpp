#include "DynamicEntity.h"

#include "Logger.h"
#include "Window.h"

DynamicEntity::DynamicEntity(double x_, double y_, Sprite* sprite_) :
    Entity(x_, y_, sprite_),
    vx(0),
    vy(0),
    speed(15),
    maxSpeed(500),
    isGrounded(false),
    levelW(0),
    levelH(0)
{
    this->rectangle = {(int)this->x, (int)this->y, (int)this->width, (int)this->height};
}

DynamicEntity::~DynamicEntity(){
    
}

void DynamicEntity::setLevelWH(unsigned int width_, unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

void DynamicEntity::updatePosition(const double dt_){
    /// @todo Fix all these magic/weird numbers.
    this->x += this->vx * dt_;

    // Left wall.
    if(this->x < 0){
        this->x = 0;
        this->vx = 0;
    }
    // Right wall.
    else if(this->x + this->width > this->levelW){
        this->x = this->levelW - this->width;
        this->vx = 0;
    }

    this->y += this->vy * dt_;

    // Top wall.
    if(this->y < 0){
        this->y = 0;
        this->vy = 0;
    }
    // Bottom wall.
    else if(this->y + this->height >= this->levelH){
        this->y = this->levelH - this->height;
        this->vy = 0;
        this->isGrounded = true;
    }
    else{
        this->isGrounded = false;
    }

    this->rectangle = {(int)this->x, (int)this->y, (int)this->width, (int)this->height};

    // Check collision with solid tiles.
    
    // for(vector<Tile*>::const_iterator it = this->tiles.begin(); it != this->tiles.end(); it++){
    //     if((*it)->isSolid()){
    //         bool collided = checkCollision(this->rectangle, (*it)->getRectangle());
    //         if(collided){
    //             this->vx = 0;
    //             this->vy = 0;
    //         }
    //     }
    // }

}

void DynamicEntity::jump(){
    this->vy = (-40) * this->speed;
}

void DynamicEntity::applyGravity(){
    this->vy += 2 * this->speed;
}

void DynamicEntity::move(bool movingLeft_, bool movingRight_){
    if(movingLeft_ || movingRight_){
        if(movingLeft_){
            this->vx -= this->speed;
            this->vx = (this->vx < -this->maxSpeed) ? -this->maxSpeed : this->vx;
        }
        if(movingRight_){
            this->vx += this->speed;
            this->vx = (this->vx > this->maxSpeed) ? this->maxSpeed : this->vx;
        }
    }
    else{
        slowVx();
    }
    
}

void DynamicEntity::slowVx(){
    this->vx *= 0.8;
}

void DynamicEntity::roll(){
    this->vx = 70 * this->speed;
}

void DynamicEntity::setTiles(std::vector<Tile*>& tiles_){
    this->tiles = tiles_;
}

#include "DynamicEntity.h"
#include "Logger.h"
#include "Collision.h"

DynamicEntity::DynamicEntity(const double x_, const double y_, Sprite* const sprite_) :
    Entity(x_, y_, sprite_),
    vx(0),
    vy(0),
    speed(20),
    maxSpeed(550),
    isGrounded(false),
    levelW(0),
    levelH(0)
{

}

DynamicEntity::~DynamicEntity(){
    
}

void DynamicEntity::setLevelWH(const unsigned int width_, const unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}

void DynamicEntity::updatePosition(const double dt_){
    /// @todo Fix all these magic/weird numbers.
    this->x += this->vx * dt_;

    if(this->vx >= 0){
        this->isRight = true;
    }
    else{
        this->isRight = false;
    }
    this->sprite->setHorizontalFlip(this->isRight);

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

    for(auto tile : this->tiles){
        if(Collision::rectsCollided(this->clip, tile->getRectangle()) && tile->isSolid()){
            this->vx = 0;
        }
    }

}

void DynamicEntity::jump(){
    this->vy = (-1) * 1500.0;
}

void DynamicEntity::applyGravity(){
    this->vy += 75;
}

void DynamicEntity::move(const bool movingLeft_, const bool movingRight_){
    const double turnHandle = 5.5;
    if(movingLeft_ || movingRight_){
        if(movingLeft_){
            if(this->vx > 0.0){
                this->vx -= this->speed * turnHandle;
            }
            else{
                this->vx -= this->speed;
            }
            
            this->vx = (this->vx < -this->maxSpeed) ? -this->maxSpeed : this->vx;
        }
        if(movingRight_){
            if(this->vx < 0.0){
                this->vx += this->speed * turnHandle;
            }
            else{
                this->vx += this->speed;
            }
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
    const double rollStrength = 120.0;
    if(this->isRight){
        this->vx = rollStrength * this->speed;
    }
    else{
        this->vx = -rollStrength * this->speed;
    }
}

void DynamicEntity::setTiles(const std::vector<Tile*>& tiles_){
    this->tiles = tiles_;   
}

void DynamicEntity::aim(Crosshair *crosshair, double direction){
    crosshair->activated = true;
    double velocity = 10;
    crosshair->x += velocity*direction;
}

void DynamicEntity::useBombPotion(BombPotion *bombPotion, int strength, int distance){
    bombPotion->activated = true;
    bombPotion->x = this->x + 100;
    bombPotion->y = this->y + 100;
    bombPotion->vx = 0;
    bombPotion->strength = strength;
    bombPotion->distance = distance;
    bombPotion->isRight = this->isRight;
}


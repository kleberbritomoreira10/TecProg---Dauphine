#include "DynamicEntity.h"
#include "Logger.h"
#include "Collision.h"

DynamicEntity::DynamicEntity(const double x_, const double y_, Sprite* const sprite_) :
    Entity(x_, y_, sprite_),
    vx(0.0),
    vy(0.0),
    speed(20.0),
    maxSpeed(550.0),
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
    this->boundingBox = {(int)this->x, (int)this->y, (int)this->width, (int)this->height};
    this->x += this->vx * dt_;
    this->y += this->vy * dt_;

    this->isRight = (this->vx >= 0.0);
    this->sprite->setHorizontalFlip(this->isRight);
}

std::array<bool, CollisionSide::SOLID_TOTAL> DynamicEntity::detectCollision(){
    std::array<bool, CollisionSide::SOLID_TOTAL> detections;
    detections.fill(false);

    for(auto tileBox : this->collisionRects){
        Collision::RectangleSide side = Collision::rectsCollidedSide(this->boundingBox, tileBox);

        switch(side){
            case Collision::RectangleSide::TOP: // Hitting under the tile.
                detections.at(SOLID_TOP) = true;
                break;
            case Collision::RectangleSide::BOTTOM: // Hitting top of the tile.
                detections.at(SOLID_BOTTOM) = true;
                break;
            case Collision::RectangleSide::RIGHT: // Hitting right side of the tile.
                detections.at(SOLID_RIGHT) = true;
                break;
            case Collision::RectangleSide::LEFT: // Hitting left side of the tile.
                detections.at(SOLID_LEFT) = true;
                break;
            case Collision::RectangleSide::NONE:
                // No collision.
                break;
            default:
                Log(ERROR) << "Unknown rectangle side collided with a dynamic entity.";
                break;
        }
    
    }

    return detections;
}

void DynamicEntity::jump(){
    this->vy = (-1) * 1000.0;
}

void DynamicEntity::applyGravity(){
    if(this->vy + 50 < this->maxSpeed*2){
        this->vy += 50;
    }
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

void DynamicEntity::aim(Crosshair* const crosshair, const double direction){
    crosshair->activated = true;
    const double velocity = 10;
    crosshair->x += velocity*direction;
}

void DynamicEntity::useBombPotion(BombPotion* const bombPotion, const int strength, const int distance){
    bombPotion->activated = true;
//    bombPotion->x = this->x + this->getWidth() - 20;

	if(this->isRight)
		bombPotion->x = this->x + this->getWidth() - bombPotion->getWidth();
	else
		bombPotion->x = this->x;
	
    bombPotion->y = this->y + 100;
    bombPotion->vx = 0;
    
    bombPotion->vy = 10;
    
//    bombPotion->vy = (-1)*20;
    bombPotion->strength = strength;
    bombPotion->distance = distance;
    bombPotion->isRight = this->isRight;
}


#include "Boss.h"
#include "Logger.h"
#include <cmath>

#include "Window.h"

Boss::Boss(const double x_, const double y_, const std::string& path_) :
	DynamicEntity(x_, y_, path_),	
	animation(nullptr),
	dead(false)
{
	this->speed = 3.0;

	this->width = 360;
	this->height = 240;

	this->animation = new Animation(0, 0, this->width, this->height, 0, false);
}

Boss::~Boss(){

}

void Boss::update(const double dt_){

	scoutPosition(dt_);

	this->animation->update(this->animationClip, dt_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(dt_);

}

void Boss::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;

	/////////////////////////////////////////////////////////////////////////////////////////
	// //Actual.
	// SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &actualRect);

	// //Bounding box.
	// SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
	// SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
	///////////////////////////////////////////////////////////////////////////////////////////

	if(this->sprite != nullptr){
		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL)
			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);
		else
			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
	}
}

void Boss::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
	if(detections_.at(CollisionSide::SOLID_TOP)){ 
		this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_BOTTOM)){		
			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_LEFT)){
		this->nextX = this->x;
		this->vx = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_RIGHT)){
		this->nextX = this->x;
		this->vx = -0.001;
	}
}

Animation *Boss::getAnimation(){
	return (this->animation);
}

void Boss::setDead(bool isDead_){
	this->dead = isDead_;
}

bool Boss::isDead(){
	return this->dead;
}

void Boss::updateBoundingBox(){
	this->boundingBox.x = (int) this->nextX + 40;
	this->boundingBox.y = (int) this->nextY + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;
}

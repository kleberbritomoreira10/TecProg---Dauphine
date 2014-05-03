#include "Collision.h"

bool Collision::rectsCollided(const SDL_Rect& a_, const SDL_Rect& b_){
    // Calculate the sides of rect A.
    const int leftA = a_.x;
    const int rightA = a_.x + a_.w;
    const int topA = a_.y;
    const int bottomA = a_.y + a_.h;

    // Calculate the sides of rect B.
    const int leftB = b_.x;
    const int rightB = b_.x + b_.w;
    const int topB = b_.y;
    const int bottomB = b_.y + b_.h;

    // If any of the sides from A are outside of B.
    if(bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB){
        return false;
    }
    // If none of the sides from A are outside B.
    else{
        return true;
    }

}

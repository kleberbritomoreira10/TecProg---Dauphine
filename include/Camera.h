#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Entity.h"
#include "Sprite.h"
#include "InputKeys.h"

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera {

	public:
		Camera();
		~Camera();

		void update();
		void setPlayerXY(double x_, double y_);
		void setLevelWH(unsigned int width_, unsigned int height_);

		SDL_Rect clip;

	private:
		double playerX;
		double playerY;
		unsigned int levelW;
		unsigned int levelH;

};

#endif //INCLUDE_CAMERA_H

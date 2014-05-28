#ifndef INCLUDE_TEXT_H
#define INCLUDE_TEXT_H

#include "SDLWrapper.h"
#include "Entity.h"

class Text : public Entity {

	public:
		Text(const double x_, const double y_, const std::string& path_, const int size_,
			const std::string& text_);

		virtual ~Text();

		/**
		* Updates the text.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Renders the text.
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

	private:
		TTF_Font* font;

};
#endif //INCLUDE_TEXT_H
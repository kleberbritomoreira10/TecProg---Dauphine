// #include "Text.h"
// #include "Logger.h"

// Text::Text(const double x_, const double y_, const std::string& path_, const int size_,
// 	const std::string& text_) :
// 	Entity(x_, y_, nullptr),
// 	font(nullptr)
// {
// 	this->font = TTF_OpenFont(path_.c_str(), size_);

// 	if(this->font == nullptr){
// 		Logger::errorSDL("Failed to open font.", TTF_GetError());
// 	}

// 	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text_.c_str(), {255, 255, 255, 255});

// 	if(surface != nullptr){
// 		this->sprite = new Sprite(surface);
// 	}
// 	else{
// 		Logger::error("Could not load font surface.");
// 	}
	
// }

// Text::~Text(){
// 	TTF_CloseFont(this->font);
// }

// void Text::update(const double dt_){
// 	(void(dt_)); //unused
// }

// void Text::render(const double cameraX_, const double cameraY_){
// 	const int dx = this->x - cameraX_;
// 	const int dy = this->y - cameraY_;
// 	this->sprite->render(dx, dy);
// }

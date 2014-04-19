#include "Configuration.h"

const unsigned int Configuration::RESOLUTION_WIDTH = 192;
const unsigned int Configuration::RESOLUTION_HEIGHT = 108;

const uint32_t Configuration::MAX_FRAMERATE = 60;
const string Configuration::TITLE = "Dauphine";

unsigned int Configuration::screenWidth = Configuration::RESOLUTION_WIDTH * 5;
unsigned int Configuration::screenHeight = Configuration::RESOLUTION_HEIGHT * 5;

unsigned int Configuration::getScreenWidth(){
	return Configuration::screenWidth;
}

unsigned int Configuration::getScreenHeight(){
	return Configuration::screenHeight;
}

#include "Configuration.h"

const unsigned int Configuration::resolutionWidth = 192;
const unsigned int Configuration::resolutionHeight = 108;

const uint32_t Configuration::maxFramerate = 60;
const string Configuration::windowTitle = "Dauphine";

unsigned int Configuration::screenWidth = Configuration::resolutionWidth * 5;
unsigned int Configuration::screenHeight = Configuration::resolutionHeight * 5;

unsigned int Configuration::getScreenWidth(){
	return Configuration::screenWidth;
}

unsigned int Configuration::getScreenHeight(){
	return Configuration::screenHeight;
}

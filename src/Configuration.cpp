#include "Configuration.h"

const unsigned int Configuration::resolutionWidth = 192;
const unsigned int Configuration::resolutionHeight = 108;

unsigned int Configuration::screenWidth = Configuration::resolutionWidth * 5;
unsigned int Configuration::screenHeight = Configuration::resolutionHeight * 5;

const int Configuration::resolutionLeftLimit = 0;
const int Configuration::resolutionRightLimit = -1860;

const uint32_t Configuration::MAX_FRAMERATE = 60;

const string Configuration::TITLE = "Dauphine";

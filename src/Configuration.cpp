#include "Configuration.h"
#include "LuaScript.h"


unsigned int Configuration::resolutionWidth = 0;
unsigned int Configuration::resolutionHeight = 0;
uint32_t Configuration::maxFramerate = 0;
string Configuration::windowTitle = "";
unsigned int Configuration::initialMultiplier = 0;
unsigned int Configuration::screenWidth = 0;
unsigned int Configuration::screenHeight = 0;


void Configuration::initialize(){
	/// @todo Make sure recieved ints are not negative.

	LuaScript luaConfig("lua/Config.lua");

	Configuration::resolutionWidth =
		(unsigned int)luaConfig.unlua_get<int>("config.resolution.width");

	Configuration::resolutionHeight =
		(unsigned int)luaConfig.unlua_get<int>("config.resolution.height");

	Configuration::maxFramerate =
		(uint32_t)luaConfig.unlua_get<int>("config.maxFramerate");

	Configuration::windowTitle = luaConfig.unlua_get<string>("config.windowTitle");

	Configuration::initialMultiplier = luaConfig.unlua_get<int>("config.initialMultiplier");

	Configuration::screenWidth =
		Configuration::resolutionWidth * Configuration::initialMultiplier;

	Configuration::screenHeight =
		Configuration::resolutionHeight * Configuration::initialMultiplier;
}

unsigned int Configuration::getResolutionWidth(){
	return Configuration::resolutionWidth;
}

unsigned int Configuration::getResolutionHeight(){
	return Configuration::resolutionHeight;
}

uint32_t Configuration::getMaxFramerate(){
	return Configuration::maxFramerate;
}

string Configuration::getWindowTitle(){
	return Configuration::windowTitle;
}

unsigned int Configuration::getInitialMultiplier(){
	return Configuration::initialMultiplier;
}

unsigned int Configuration::getScreenWidth(){
	return Configuration::screenWidth;
}

unsigned int Configuration::getScreenHeight(){
	return Configuration::screenHeight;
}

#ifndef INCLUDE_CONFIGURATION_H
#define INCLUDE_CONFIGURATION_H

#include <string>

using std::string;

/**
* Game configuration class.
* @todo Properly implement and refactor the Configuration.
*/
class Configuration {
	public:
		const static unsigned int resolutionWidth; /**< The game's width resolution. */
		const static unsigned int resolutionHeight; /**< The game's height resolution. */

		const static uint32_t MAX_FRAMERATE; /**< The game's max framerate. */
		const static string TITLE; /**< The game window's title. */

		static unsigned int screenWidth; /**< The screen width. */
		static unsigned int screenHeight; /**< The screen height. */
		
};

#endif //INCLUDE_CONFIGURATION_H

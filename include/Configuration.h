#ifndef INCLUDE_CONFIGURATION_H
#define INCLUDE_CONFIGURATION_H

#include <string>

using std::string;

/**
* Game configuration class.
* @todo Properly implement with lua and refactor the Configuration.
*/
class Configuration {
	public:
		const static unsigned int resolutionWidth; /**< The game's width resolution. */
		const static unsigned int resolutionHeight; /**< The game's height resolution. */

		const static int resolutionLeftLimit; /**< The game's limit in left side. */
		const static int resolutionRightLimit; /**< The game's limit int right side. */

		const static uint32_t MAX_FRAMERATE; /**< The game's max framerate. */
		const static string TITLE; /**< The game window's title. */

		static unsigned int screenWidth; /**< The screen width. */
		static unsigned int screenHeight; /**< The screen height. */

		static unsigned int rightLimit; /**< The screen width. */
		static unsigned int leftLimit; /**< The screen height. */	
};

#endif //INCLUDE_CONFIGURATION_H

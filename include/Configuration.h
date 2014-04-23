#ifndef INCLUDE_CONFIGURATION_H
#define INCLUDE_CONFIGURATION_H

#include <string>
using std::string;

/**
* Game configuration class.
* @todo Properly implement with lua(?) and refactor the Configuration.
*/
class Configuration {

	public:
		/**
		* Initializes all the attributes.
		*/
		static void initialize();

		/**
		* @return resolutionWidth
		*/
		static unsigned int getResolutionWidth();

		/**
		* @return resolutionHeight
		*/
		static unsigned int getResolutionHeight();

		/**
		* @return maxFramerate
		*/
		static uint32_t getMaxFramerate();

		/**
		* @return windowTitle
		*/
		static string getWindowTitle();

		/**
		* @return initialMultiplier
		*/
		static unsigned int getInitialMultiplier();

		/**
		* @return The current screen width.
		*/
		static unsigned int getScreenWidth();

		/**
		* @return The current screen height.
		*/
		static unsigned int getScreenHeight();

	private:
		static unsigned int resolutionWidth; /**< The game's width resolution. */
		static unsigned int resolutionHeight; /**< The game's height resolution. */

		static uint32_t maxFramerate; /**< The game's max framerate. */
		static string windowTitle; /**< The game window's title. */

		static unsigned int initialMultiplier; /**< The initial multiplier for the
			resolutions. */

		static unsigned int screenWidth; /**< The screen width. */
		static unsigned int screenHeight; /**< The screen height. */

};

#endif //INCLUDE_CONFIGURATION_H

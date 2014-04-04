#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>

using std::string;

/**
* Class used for logging.
* No instances are needed, all the methods are static.
*/
class Logger {
	/// @todo Implement a separate generic parameter log function, to log and integer, for example.

	public:
		/**
		* The default logger.
		* Logs the desired message with a "Log: " prefix.
		* @param message_ : the message to log.
		*/
		static void log(const string message_);

		/**
		* The logger for warnings.
		* Logs the desired message with a "Warning: " prefix.
		* @param message_ : the message to log.
		*/
		static void warning(const string message_);

		/**
		* The logger for errors.
		* Logs the desired message with an "Error: " prefix.
		* @param message_ : the message to log.
		*/
		static void error(const string message_);

		/**
		* The logger for internal SDL errors.
		* Logs the desired message with an "Error: " prefix, accompanied by the error string returned by the GetError() from the SDL libraries.
		* @param message_ : the message to log.
		* @param messageSDL_ : the error string from SDL to log.
		* @see SDL_GetError()
		* @see IMG_GetError()
		*/
		static void errorSDL(const string message_, const char *messageSDL_);

};

#endif //INCLUDE_LOGGER_H

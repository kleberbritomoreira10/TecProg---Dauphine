#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>

using std::string;

class Logger{
	public:
		/**
		* The default logger.
		* Logs the desired message with a "Log: " prefix.
		* @params message : the message to log.
		*/
		static void log(const string message);

		/**
		* The logger for warnings.
		* Logs the desired message with a "Warning: " prefix.
		* @params message : the message to log.
		*/
		static void warning(const string message);

		/**
		* The logger for errors.
		* Logs the desired message with a "Error: " prefix.
		* @params message : the message to log.
		*/
		static void error(const string message);

		/**
		* The logger for internal SDL errors.
		* Logs the desired message with a "Error: " prefix, accompanied by the error string returned by the GetError() from the SDL libraries.
		* @params message : the message to log.
		* @params messageSDL : the error string from SDL.
		*/
		static void errorSDL(const string message, const char *messageSDL);
};

#endif //INCLUDE_LOGGER_H

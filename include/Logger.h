#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>

using std::string;

class Logger{
	public:
		/* Logger with a prefix of "Log: " */
		static void log(const string message);
		/* Logger with a prefix of "Warning: " */
		static void warning(const string message);
		/* Logger with a prefix of "Error: " */
		static void error(const string message);
		/* Logger with a prefix of "Error: ", and supports the GetError() functions */
		static void errorSDL(const string message, const char *messageSDL);
};

#endif //INCLUDE_LOGGER_H

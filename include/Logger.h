#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>

using std::string;

class Logger{
	public:
		static void log(const string message);
		static void warning(const string message);
		static void error(const string message);

		static void errorSDL(const string message, const char *messageSDL);
};

#endif //INCLUDE_LOGGER_H

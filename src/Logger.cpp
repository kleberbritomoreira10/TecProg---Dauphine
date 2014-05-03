#include "Logger.h"
#include <iostream>

bool Logger::isVerbose = false;

void Logger::log(const std::string& message_){
	/// @todo Implement a separate generic parameter log function, to log an integer, for example.
	std::cerr << "[Log]:     " << message_ << std::endl;
}

void Logger::warning(const std::string& message_){
	std::cerr << "[Warning]: " << message_ << std::endl;
}

void Logger::error(const std::string& message_){
	std::cerr << "[Error]:   " << message_ << std::endl;
}

void Logger::errorSDL(const std::string& message_, const char* messageSDL_){
	std::cerr << "[Error]:   " << message_ << std::endl;
	std::cerr << "   [SDL Error]: " << std::string(messageSDL_) << std::endl;
}

void Logger::verbose(const std::string& message_){
	if(Logger::isVerbose){
		std::cerr << "[Verbose]: " << message_ << std::endl;
	}
}

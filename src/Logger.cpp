#include "Logger.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

void Logger::log(const string message){
	cerr << "Log: " << message << endl;
}

void Logger::warning(const string message){
	cerr << "Warning: " << message << endl;
}

void Logger::error(const string message){
	cerr << "Error: " << message << endl;
}

void Logger::errorSDL(const string message, const char *messageSDL){
	cerr << "Error: " << message << endl;
	cerr << "SDL Error: " << std::string(messageSDL) << endl;
}

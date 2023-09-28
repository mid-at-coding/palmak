#include <iostream>
#include "error.hpp"

// this file should really be renamed

Logger::severity Logger::outputThreshold = Logger::DEBUG;

std::string Logger::levelToStr(int sev){
	switch(sev){
		case DEBUG:
			return "[DEBUG]";
		case INFO:
			return "[INFO]";
		case WARN:
			return "[WARN]";
		case NONFATAL:
			return "[NONFATAL]";
		case FATAL: 
			return "[FATAL]";
		case NOTAG:
			return "";
		default: // ??
			return "[FATAL]";
	}
}
void Logger::log(std::string msg, severity sev, int indentation){
	if(sev < outputThreshold)
		return;
	std::cout <<levelToStr(sev);
	for(int i = 0; i < indentation; i++)
		std::cout << "  ";
	std::cout << msg << std::endl;
}

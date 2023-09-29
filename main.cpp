/*	palmak 1.0 made by catto
 *	You can use this for anything you want
 *	If you use this code credit me
 *	cattodoameow@proton.me
 */

#include <iostream>
#include <vector>
#include <string>
#include "parse.hpp"
#include "error.hpp"
#include "color.hpp"
#include "conversion.hpp"
#include "formatting.hpp"
#include <sstream>

void outputColors(std::vector<Color>, bool);

std::vector<Color> calculateColors(arguments);

int main(int argc, char** argv){
	std::vector<std::string> argv_cpp;
	std::string _temp;
	arguments args;
	// setup
	for(int i = 0; i < argc; i++){
		for(int k = 0; argv[i][k] != '\0'; k++){
			_temp += argv[i][k];
		}
		argv_cpp.push_back(_temp);
		_temp.clear();
	}
	Logger logger;
	if(argc < 2){
		logger.log("Not enough arguments! Run palmak help for usage", Logger::FATAL);
		return 0;
	}
	args = parse(argv_cpp);
	outputColors(calculateColors(args), args.color);
}

void outputColors(std::vector<Color> args, bool color){
	Logger logger;
	std::string out;
	std::stringstream ss;
	for(int i = 0; i < args.size(); i++){
		ss.clear();
		out.clear();
		ss << std::hex << std::uppercase <<
			(unsigned)(args[i].getRGB().value().r &0xFF) <<
			(unsigned)(args[i].getRGB().value().g &0xFF) <<
			(unsigned)(args[i].getRGB().value().b &0xFF);
		ss >> out;
		if(color)
			out = colorString(out,args[i]);
		std::cout << out << std::endl;
	}
}

std::vector<Color> calculateColors(arguments args){
	std::vector<Color> colors;
	Logger logger;
	HSV lightest;
	HSV temp;
	const HSV diff = { args.hueshift, args.satshift, args.valueshift };
	RGB tempRGB;
	try{
		lightest = args.base.getHSV().value();
	}
	catch(std::bad_optional_access){
		logger.log("No base color inputted!",Logger::FATAL);
		exit(0);
	}
	for(int i = 0; i < args.width; i++)
		lightest += diff;

	for(int i = 0; i < args.width * 2 + 1; i++)
		colors.push_back(Color(lightest));

	for(int i = 1; i < colors.size(); i++){
		for(int k = i; k < colors.size(); k++){
			temp = colors[k].getHSV().value();
			temp -= diff;
			colors[k].set(temp);
		}
	}
	return colors;
}

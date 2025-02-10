/*	palmak 1.2 made by catto
 *	You can use this for anything you want
 *	If you use this code credit me
 *	cattodoameow@proton.me
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "parse.hpp"
#include "error.hpp"
#include "color.hpp"
#include "conversion.hpp"
#include "formatting.hpp"
#include <sstream>

void outputColors(std::vector<Color>, const bool, const bool);

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
		logger.log("Not enough arguments, displaying help text instead", Logger::INFO);
		helpText();
		return 0;
	}
	args = parse(argv_cpp);
	outputColors(calculateColors(args), args.color, args.text);
}

void outputColors(std::vector<Color> args, const bool color, const bool text){
	Logger logger;
	std::string out;
	std::stringstream ss;
	for(int i = 0; i < args.size(); i++){
		ss.clear();
		out.clear();
		logger.log("hue: " + std::to_string(args[i].getHSV().value().h), Logger::DEBUG);
		logger.log("sat: " + std::to_string(args[i].getHSV().value().s), Logger::DEBUG);
		logger.log("val: " + std::to_string(args[i].getHSV().value().v), Logger::DEBUG);
		if(text){
			ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') <<
				(unsigned)(args[i].getRGB().value().r &0xFF);
			ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') <<
				(unsigned)(args[i].getRGB().value().g &0xFF);
			ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') <<
				(unsigned)(args[i].getRGB().value().b &0xFF);
			ss >> out;
		}
		else{
			out = "      "; // this shit is so easy
		}
		if(color)
			out = colorString(" " + out + " ", args[i], true); //+ colorString("\u2588", args[i]);
		std::cout << out << std::endl;
	}
}

std::vector<Color> calculateColors(arguments args){
	std::vector<Color> colors;
	Logger logger;
	HSV base;
	HSV temp;
	const HSV diff = { args.hueshift, args.satshift, args.valueshift };
	RGB tempRGB;
	try{
		base = args.base.getHSV().value();
	}
	catch(std::bad_optional_access){
		logger.log("No base color inputted!",Logger::FATAL);
		exit(0);
	}

	// generate array
	for(int i = 0; i < args.width * 2 + 1; i++)
		colors.push_back(Color(base));

	for(int i = 1; i < args.width + 1; i++){
		for(int k = 0; k < i; k++){
			// darken colors on low side
			temp = colors[k].getHSV().value();
			temp += diff;
			colors[k].set(temp);
			logger.log("k: " + std::to_string(k) + " colors.size(): " + std::to_string(colors.size()), Logger::DEBUG);
			// brighten colors on high side
			temp = colors[colors.size() - k - 1].getHSV().value();
			temp -= diff;
			colors[colors.size() - k - 1].set(temp);
		}
	}
	return colors;
}

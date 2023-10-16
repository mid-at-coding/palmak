#include "parse.hpp"
#include <iostream>
#include "error.hpp"
#include <sstream>
#include "color.hpp"

static void tolower(std::string& in){
	for(int i = 0; i < in.size(); i++)
		in[i] = tolower(in[i]);
}
static HSV cslToHSV(std::string inp){
	HSV ret = { 0, 0, 0 };
	Logger logger;
	std::string strings[3];
	for(int k = 0, i = 0; i < inp.size(); i++){
		if(inp[i] == ','){
			k++;
			if(k > 3){
				logger.log("HSV input too long, ignoring extra values", Logger::NONFATAL);
				break;
			}
		}
		else{
			strings[k] += inp[i];
		}

	}
	try{
		ret.h = std::stoi(strings[0]);
		ret.s = std::stoi(strings[1]);
		ret.v = std::stoi(strings[2]);
	}
	catch(std::invalid_argument){
		logger.log("Incorrect arguments! Usage: palmak hsv xx,xx,xx", Logger::FATAL);
	}
	return ret;
}
static RGB hexToRGB(std::string inp){
	Logger logger;
	if(inp.size() < 6){
		logger.log("Hex input shorter than 6 characters", Logger::FATAL);
		exit(0);
	}
	std::string color[3] = {
		inp.substr(0,2),
		inp.substr(2,2),
		inp.substr(4,6)
	};
	if(inp.size() > 6)
		logger.log("Hex input longer than 6 characters, extra characters ignored", Logger::WARN);
	unsigned int vals[3];
	std::stringstream ss;
	RGB ret;
	for(int i = 0; i < 3; i++){
		ss << std::hex << color[i];
		ss >> vals[i];
		ss.clear();
	}
	ret.r = vals[0];
	ret.g = vals[1];
	ret.b = vals[2];
	return ret;
}

static int oneArgCMD(const std::vector<std::string> args, int& i, const std::string invalidmsg, const std::string missingArgsMsg = "Missing arguments! Run palmak help for usage!"){
	Logger logger;
	if(args.size() <= i + 1){ // there is no next argument
		logger.log(missingArgsMsg,Logger::FATAL);
		exit(0);
	}
	try{
		return std::stoi(args[++i]);
	}
	catch(std::invalid_argument){
		logger.log(invalidmsg ,Logger::FATAL);
		exit(0);
	}
}

arguments parse(std::vector<std::string> args){
	Logger logger;
	arguments ret;
	bool colorSet = false;
	bool validCommand = false;

	for(int i = 0; i < args.size(); i++)
		tolower(args[i]);

	for(int i = 1; i < args.size();i++){
		if(args[i] == "help"){
			helpText();
			exit(0);
		}
		if(args[i] == "h" || 
		   args[i] == "hex"){
			validCommand = true;
			if(args.size() <= i + 1){ // there is no next argument
				logger.log("Missing arguments! Run palmak help(Make sure not to put a # in front)",Logger::FATAL);
				exit(0);
			}
			if(colorSet)
				logger.log("Color respecified, replacing with " + args[i],Logger::WARN);
			colorSet = true;
			i++;
			ret.base.set(hexToRGB(args[i]));
		}
		if(args[i] == "hsv"){
			validCommand = true;
			if(args.size() <= i + 1){ // there is no next argument
				logger.log("Missing arguments! Run palmak help for usage!",Logger::FATAL);
				exit(0);
			}
			i++;
			if(args[i].find(',') == std::string::npos){
				logger.log("HSV must be comma seperated",Logger::FATAL);
				exit(0);
			}
			ret.base.set(cslToHSV(args[i]));
		}
		if(args[i] == "c" ||
		   args[i] == "count"){
			validCommand = true;
			if ((ret.width = oneArgCMD(args, i, "Invalid count!")) < 0){
				logger.log("Invalid count!", Logger::FATAL);
				exit(0);
			}
		}

		if(args[i] == "hs" ||
		   args[i] == "hueshift"){
			validCommand = true;
			ret.hueshift = oneArgCMD(args, i, "Invalid hueshift!");
		}

		if(args[i] == "vs" ||
		   args[i] == "valueshift"){
			validCommand = true;
			ret.valueshift = oneArgCMD(args, i, "Invalid valueshift!");
		}

		if(args[i] == "ss" ||
		   args[i] == "satshift" ||
		   args[i] == "saturationshift"){
			validCommand = true;
			ret.satshift = oneArgCMD(args, i, "Invalid satshift!");
		}

		if(args[i] == "nc" ||
		   args[i] == "nocolor"){
			validCommand = true;
			ret.color = false;
			if(ret.text == false)
				logger.log("Both text and color disabled, are you sure you just want blank output?", Logger::WARN);
		}
		if(args[i] == "v" ||
		   args[i] == "verbose"){
			validCommand = true;
			ret.verbose = true;
			Logger::outputThreshold = Logger::DEBUG;
		}
		if(args[i] == "nt" ||
		   args[i] == "notext"){
			validCommand = true;
			ret.text = false;
			if(ret.color == false)
				logger.log("Both text and color disabled, are you sure you just want blank output?", Logger::WARN);
		}
		if(!validCommand){
			logger.log("Invalid command \"" + args[i] + "\", run palmak help for help", Logger::FATAL);
			exit(0);
		}
		validCommand = false;
	}
	return ret;
}

void helpText(){
	Logger logger;	
	logger.log("Pal[lete]Mak[er] v1.0 by catto",Logger::NOTAG);
	logger.log("A lightweight, simple pallete maker",Logger::NOTAG);
	logger.log("Usage: palmak {h[ex] | hsv} [options]",Logger::NOTAG);
	logger.log("arguments:",Logger::NOTAG);
	logger.log("help			This output",Logger::NOTAG,1);
	logger.log("h[ex]			The base color of the pallete, in hex",Logger::NOTAG,1);
	logger.log("hsv			The base color of the pallete, in hsv(comma seperated)",Logger::NOTAG,1);
	logger.log("c[ount]		The amount of colors in both directions from the base color (default 2)",Logger::NOTAG,1);
	logger.log("h[ue]s[hift]		Specificy the amount and direction of the hueshift, in degrees (default 9)",Logger::NOTAG,1);
	logger.log("v[alue]s[hift]	Specificy the amount and direction of the value shift, in % (default -10%)",Logger::NOTAG,1);
	logger.log("s[at]s[hift]		Specificy the amount and direction of the saturation shift, in degrees (default 12)",Logger::NOTAG,1);
	logger.log("n[o]c[olor]		Disable color output",Logger::NOTAG,1);
	logger.log("n[o]t[ext]		Disable text, only output colors",Logger::NOTAG,1);

}

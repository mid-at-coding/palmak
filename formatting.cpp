#include "formatting.hpp"

std::string colorString(std::string msg, Color color){
	RGB rgb = color.getRGB().value(); // possible crash, catch?
	return ("\e[38;2;" + std::to_string(rgb.r) + ";" + std::to_string(rgb.g) + ";" + std::to_string(rgb.b) + "m" + msg + "\e[0m");
}

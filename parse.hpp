#include "color.hpp"
#include <vector>
#include <string>

struct arguments{
	Color base;
	int width = 2;
	int hueshift = 9;
	int valueshift = -10;
	int satshift = 12;
	bool color = true;
	bool verbose = false;
	bool text = true;
};

arguments parse(std::vector<std::string> args);

void helpText();

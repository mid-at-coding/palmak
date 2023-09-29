#include "color.hpp"
#include <cmath>
#include <optional>

std::optional<RGB> Color::getRGB(){
	if(!_set)
		return {};
	return {rgb};
}
std::optional<HSV> Color::getHSV(){
	if(!_set)
		return {};
	return {hsv};
}

HSV& HSV::operator+=(const HSV& in){
	// hue
	if(in.h + h > 360)
		h = std::abs(in.h - h);
	else
		h += in.h;
	
	// saturation
	if(in.s + s > 100)
		s = 100;
	else
		s += in.s;

	// value
	if(in.v + v > 100)
		v = 100;
	else
		v += in.v;
	return (*this);
}

HSV& HSV::operator-=(const HSV& in){
	// hue
	if(in.h > h)
		h = 360 - (h - in.h);
	else
		h -= in.h;

	// saturation
	if(in.s > s)
		s = 0;
	else
		s -= in.s;

	// value
	if(in.v > v)
		v = 0;
	else
		v -= in.v;
	return(*this);
}

void Color::set(RGB v){
	_set = true;
	rgb = v;
	hsv = v;
}
void Color::set(HSV v){
	_set = true;
	rgb = v;
	hsv = v;
}

Color::Color(HSV v){
	set(v);
}

Color::Color(RGB v){
	set(v);
}

Color::Color(){

}


std::string RGBtos(const RGB& in){
	return std::to_string(in.r) + ", " + std::to_string(in.g) + ", " + std::to_string(in.b);
}

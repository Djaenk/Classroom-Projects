#include "AmateurBoxer.h"

Amateur::Amateur(std::string golden_gloves, std::string name, int wins, int losses):Boxer(name, wins, losses){
	this->golden_gloves = golden_gloves;
}

std::string Amateur::toString(){
	std::string string = "";
	string += name;
	string += "  wins: ";
	string += std::to_string(wins);
	string += "  losses: ";
	string += std::to_string(losses);
	string += "  ";
	string += golden_gloves;
	return string;
}
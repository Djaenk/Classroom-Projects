#include "Boxer.h"

Boxer::Boxer(std::string name, int wins, int losses){
	this->name = name;
	this->wins = wins;
	this->losses = losses;
}

std::string Boxer::toString(){
	std::string string = "";
	string += name;
	string += "  wins: ";
	string += std::to_string(wins);
	string += "  losses: ";
	string += std::to_string(losses);
	return string;
}
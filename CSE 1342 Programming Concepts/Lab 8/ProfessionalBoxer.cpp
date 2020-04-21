#include "ProfessionalBoxer.h"

Professional::Professional(std::string athletic_commission, std::string name, int wins, int losses):Boxer(name, wins, losses){
	this->athletic_commission = athletic_commission;
}

std::string Professional::toString(){
	std::string string = "";
	string += name;
	string += "  wins: ";
	string += std::to_string(wins);
	string += "  losses: ";
	string += std::to_string(losses);
	string += "  ";
	string += athletic_commission;
	return string;
}
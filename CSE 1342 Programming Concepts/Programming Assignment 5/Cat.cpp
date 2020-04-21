#include "Cat.h"
#include <iostream>

Cat::Cat(std::string name, int age, bool isOutdoor){
	this->name = name;
	this->age = age;
	this->isOutdoor = isOutdoor;	
}

void Cat::print(){
	std::cout << "Animal: " << "Cat" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Fee: " << dailyFee << std::endl;
	std::cout << "Indoor/Outdoor: ";
	if(isOutdoor){
		std::cout << "Outdoor" << std::endl;
	}
	else{
		std::cout << "Indoor" << std::endl;
	}
}
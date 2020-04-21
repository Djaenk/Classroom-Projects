#include "Rabbit.h"
#include <iostream>

Rabbit::Rabbit(std::string name, int age, int numberOfCarrots){
	this->name = name;
	this->age = age;
	this->numberOfCarrots = numberOfCarrots;	
}

void Rabbit::print(){
	std::cout << "Animal: " << "Rabbit" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Fee: " << dailyFee << std::endl;
	std::cout << "Number of Carrots / Day: " << numberOfCarrots << std::endl;
}
#include "Dog.h"
#include <iostream>

Dog::Dog(std::string name, int age, std::string favoriteToy){
	this->name = name;
	this->age = age;
	this->favoriteToy = favoriteToy;	
}

void Dog::print(){
	std::cout << "Animal: " << "Dog" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Fee: " << dailyFee << std::endl;
	std::cout << "Favorite Toy: " << favoriteToy << std::endl;
}
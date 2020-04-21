#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "AnimalsList.h"

void dropOff(AnimalsList &daycare, std::string species, std::string information){
	std::stringstream info(information);
	if(species == "cat"){
		std::string name;
		std::string age;
		std::string isOutdoor;
		std::getline(info, name, ',');
		std::getline(info, age, ',');
		std::getline(info, isOutdoor, '\n');
		daycare.addAnimal(new Cat(name, std::stoi(age), (isOutdoor == "true")));
	}
	else if(species == "dog"){
		std::string name;
		std::string age;
		std::string favoriteToy;
		std::getline(info, name, ',');
		std::getline(info, age, ',');
		std::getline(info, favoriteToy, '\n');
		daycare.addAnimal(new Dog(name, std::stoi(age), favoriteToy));
	}
	else if(species == "rabbit"){
		std::string name;
		std::string age;
		std::string numberOfCarrots;
		std::getline(info, name, ',');
		std::getline(info, age, ',');
		std::getline(info, numberOfCarrots, '\n');
		daycare.addAnimal(new Rabbit(name, std::stoi(age), std::stoi(numberOfCarrots)));
	}
}

int main(int argc, char **argv){
	AnimalsList daycare;
	
	//add preexisting animals
	std::ifstream animals;
	animals.open(argv[1]);
	if(!animals.is_open()){
		std::cout << "Invalid input file." << std::endl;
		exit(EXIT_FAILURE);
	}
	while(animals.peek() != EOF){
		std::string species;
		std::string information;
		std::getline(animals, species, ',');
		std::getline(animals, information, '\n');
		dropOff(daycare, species, information);
	}

	//UI
	int choice = -1;
	while(choice != 0){
		std::cout << std::endl;
		std::cout << "Select an option:" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. View Animals" << std::endl;
		std::cout << "2. Drop Off Animal" << std::endl;
		std::cout << "3. Pick Up Animal" << std::endl;
		std::cout << "Option: ";
		std::cin >> choice;
		if(choice == 0){
			break;
		}
		if(choice == 1){
			daycare.print();
		}
		else if(choice == 2){
			char species;
			std::string information;
			std::cout << std::endl;
			std::cout << "What animal are you dropping off? (c,d,r): ";
			std::cin >> species;
			if(species == 'c'){
				std::cout << "Enter your cat's information in the following format:" << std::endl;
				std::cout << "name,age,isOutdoor" << std::endl;
				std::cout << "Ex: elroy,1,true" << std::endl;
				std::cin >> information;
				dropOff(daycare, "cat", information);
				std::cout << std::endl;
				std::cout << "Thank you!" << std::endl;
			}
			else if(species == 'd'){
				std::cout << "Enter your dog's information in the following format:" << std::endl;
				std::cout << "name,age,favoriteToy" << std::endl;
				std::cout << "Ex. george,1,bone" << std::endl;
				std::cin >> information;
				dropOff(daycare, "dog", information);
				std::cout << std::endl;
				std::cout << "Thank you!" << std::endl;
			}
			else if(species == 'r'){
				std::cout << "Enter your rabbit's information in the following format:" << std::endl;
				std::cout << "name,age,numberOfCarots" << std::endl;
				std::cout << "Ex. billy,1,3" << std::endl;
				std::cin >> information;
				dropOff(daycare, "rabbit", information);
				std::cout << std::endl;
				std::cout << "Thank you!" << std::endl;
			}
			else{
				std::cout << "Sorry, we don't accept animals of that type." << std::endl;
			}
		}
		else if(choice == 3){
			int cage;
			std::cout << std::endl;
			std::cout << "Which animal would you like to pick up?" << std::endl;
			std::cout << "Enter Cage #: ";
			std::cin >> cage;
			if(!daycare.removeAnimal(cage)){
				std::cout << "There does not exist an animal with that cage number." << std::endl;
			}
		}
		else{
			std::cout << std::endl;
			std::cout << "Please make a valid selection" << std::endl;
		}
	}
}
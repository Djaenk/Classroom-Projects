#include "AnimalsList.h"
#include <iostream>

void AnimalsList::addAnimal(Animal* animal){
	if(head == nullptr){
		head = animal;
		tail = animal;
	}
	else{
		tail->setNextAnimal(animal);
		tail = animal;
	}
}

bool AnimalsList::removeAnimal(int cage_number){
	if(head == nullptr){
		return false;
	}
	Animal* previous_animal = nullptr;
	Animal* to_remove = head;
	Animal* next_animal;
	if(cage_number == 1){
		next_animal = to_remove->getNextAnimal();
		head = next_animal;
	}
	else{
		previous_animal = head;
		for(int i = 2; i < cage_number; i++){
			previous_animal = previous_animal->getNextAnimal();
			if(previous_animal == tail){
				return false;
			}
		}
		to_remove = previous_animal->getNextAnimal();
		next_animal = to_remove->getNextAnimal();
		previous_animal->setNextAnimal(next_animal);
	}
	if(tail == to_remove){
		tail = previous_animal;
	}
	delete to_remove;
	return true;
}

void AnimalsList::print(){
	Animal* animal = head;
	std::cout << std::endl;
	if(animal == nullptr){
		std::cout << "We do not have any animals at the moment." << std::endl;
		return;
	}
	std::cout << "===========================================";
	for(int i = 1; animal != nullptr; i++){
		std::cout << std::endl;
		std::cout << "------ Cage " << i << " ------" << std::endl;
		animal->print();
		animal = animal->getNextAnimal();
	}
	std::cout << "===========================================" << std::endl;
}
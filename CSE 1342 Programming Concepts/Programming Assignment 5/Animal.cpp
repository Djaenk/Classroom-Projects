#include "Animal.h"

Animal* Animal::getNextAnimal(){
	return next_animal;
}

void Animal::setNextAnimal(Animal* next_animal){
	this->next_animal = next_animal;
}
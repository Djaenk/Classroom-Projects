#ifndef ANIMALS_LIST
#define ANIMALS_LIST

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "Rabbit.h"

class AnimalsList{
	private:
		Animal* head = nullptr;
		Animal* tail = nullptr;
	public:
		void addAnimal(Animal* animal);
		bool removeAnimal(int cage_number);
		void print();
};

#endif
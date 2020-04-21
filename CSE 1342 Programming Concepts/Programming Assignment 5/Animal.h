#ifndef ANIMAL
#define ANIMAL

#include <string>

class Animal{
	protected:
		std::string name;
		int age;
		int dailyFee;
		Animal* next_animal = nullptr;
	public:
		Animal* getNextAnimal();
		void setNextAnimal(Animal* next_animal);
		virtual void print() = 0;
};

#endif
#ifndef DOG
#define DOG

#include "Animal.h"

class Dog : public Animal{
	private:
		int dailyFee = 50;
		std::string favoriteToy;
	public:
		Dog(std::string name, int age, std::string favoriteToy);
		void print();
};

#endif
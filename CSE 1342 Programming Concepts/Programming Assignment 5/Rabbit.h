#ifndef RABBIT
#define RABBIT

#include "Animal.h"

class Rabbit : public Animal{
	private:
		int dailyFee = 15;
		int numberOfCarrots;
	public:
		Rabbit(std::string name, int age, int numberOfCarrots);
		void print();
};

#endif
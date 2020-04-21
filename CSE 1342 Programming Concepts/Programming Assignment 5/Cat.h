#ifndef CAT
#define CAT

#include "Animal.h"

class Cat : public Animal{
	private:
		int dailyFee = 25;
		bool isOutdoor;
	public:
		Cat(std::string name, int age, bool isOutdoor);
		void print();
};

#endif
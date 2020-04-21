#include <iostream>
#include "Boxer.h"
#include "ProfessionalBoxer.h"
#include "AmateurBoxer.h"

int main() {
	const unsigned numBoxers = 3;
	Boxer* boxers[numBoxers] = {
		new Boxer("Joe Smith", 10, 3),
		new Professional("Texas Athletic Commission" , "Fred Jackson", 4, 5),
		new Amateur("Dallas Golden Gloves" , "Tommy Johnson", 3, 3)
	};
	for(unsigned i = 0; i < numBoxers; i++){
		std::cout << boxers[i]->toString() << std::endl;
	}
	return 0;
}
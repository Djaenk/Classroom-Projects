#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "search_functions.h"

int main() {
	std::vector<std::string> test{"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	assert(searchIterative(test, "A") == 0);
	assert(searchRecursive(test, "A") == 0);
	test = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	assert(searchIterative(test, "I") == 8);
	assert(searchRecursive(test, "I") == 8);
	test = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	assert(searchIterative(test, "D") == 3);
	assert(searchRecursive(test, "D") == 3);
	test = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	assert(searchIterative(test, "H") == 7);
	assert(searchRecursive(test, "H") == 7);
	test = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	assert(searchIterative(test, "E") == 4);
	assert(searchRecursive(test, "E") == 4);
	std::cout << "Success" << std::endl;
}
#include <iostream>
#include <vector>
#include <string>
#include "search_functions.h"

int main() {
	std::vector<std::string> test{"A", "B", "C", "D", "E"};
	std::cout << searchIterative(test, "A") << std::endl;
	std::cout << searchRecursive(test, "A") << std::endl;
}
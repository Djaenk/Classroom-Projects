#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "search_functions.h"

int prompt(){
	int choice = 0;
	while(choice < 1 || choice > 5){
		std::cout << "Welcome to SMU's Phone Book" << std::endl << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "(1) - Find By Name (recursive)" << std::endl;
		std::cout << "(2) - Find By Name (iterative)" << std::endl;
		std::cout << "(3) - Find By Phone Number (recursive)" << std::endl;
		std::cout << "(4) - Find By Phone Number (iterative)" << std::endl;
		std::cout << "(5) - Quit" << std::endl << std::endl;
		std::cout << "Please Select an Option: ";
		std::cin >> choice;
    }
	return choice;
}
int main(){
	std::ifstream phonebook;
	phonebook.open("phoneBook.txt");
	std::vector<std::string> names;
	std::vector<std::string> numbers;
	while(phonebook.peek() != EOF){
		std::string name = "";
		std::getline(phonebook, name, ',');
		names.push_back(name);
		std::string number = "";
		std::getline(phonebook, number, '\n');
		numbers.push_back(number);
    }
	while(true){
		int choice = prompt();
		if (choice == 1){
			std::string name = "";
			std::cout << "Enter a Name";
			std::cin >> name;
			int index = searchRecursive(names, name);
			if (index == -1){
				std::cout << std::endl << "That name does not exist in the phonebook." << std::endl << std::endl;
			}
			else {
				std::cout << std::endl << index << ". " << names[index] << " - " << numbers[index] << std::endl << std::endl;
			}
		}
		else if (choice == 2){
			std::string name = "";
			std::cout << "Enter a Name";
			std::cin >> name;
			int index = searchIterative(names, name);
			if (index == -1){
				std::cout << std::endl << "That name does not exist in the phonebook." << std::endl << std::endl;
			}
			else {
				std::cout << std::endl << index << ". " << names[index] << " - " << numbers[index] << std::endl << std::endl;
			}
		}
		else if (choice == 3){
			std::string number = "";
			std::cout << "Enter a Number";
			std::cin >> number;
			int index = searchRecursive(numbers, number);
			if (index == -1){
				std::cout << std::endl << "That number does not exist in the phonebook." << std::endl << std::endl;
			}
			else {
				std::cout << std::endl << index << ". " << names[index] << " - " << numbers[index] << std::endl << std::endl;
			}
		}
		else if (choice == 4){
			std::string number = "";
			std::cout << "Enter a Number";
			std::cin >> number;
			int index = searchIterative(numbers, number);
			if (index == -1){
				std::cout << std::endl << "That number does not exist in the phonebook." << std::endl << std::endl;
			}
			else {
				std::cout << std::endl << index << ". " << names[index] << " - " << numbers[index] << std::endl << std::endl;
			}
		}
		else if (choice == 5){
			break;
		}
	}
}
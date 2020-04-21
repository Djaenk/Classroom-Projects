#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "search_functions.h"

void readPhoneBook(std::string file_name, std::vector<std::string> &names, std::vector<std::string> &numbers){
	names.clear();
	numbers.clear();
	std::ifstream phonebook;
	phonebook.open(file_name);
	std::string name = "";
	std::string number = "";
	while(phonebook.peek() != EOF){
		std::getline(phonebook, name, ',');
		names.push_back(name);
		std::getline(phonebook, number);
		numbers.push_back(number);
    }
	phonebook.close();
}

int prompt(){
	int choice;
	std::cout << "Please Select an Option: ";
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore();
	return choice;
}
int main(){
	std::vector<std::string> names;
	std::vector<std::string> numbers;
	std::cout << "Welcome to SMU's Phone Book" << std::endl << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "(1) - Find By Name (recursive)" << std::endl;
	std::cout << "(2) - Find By Name (iterative)" << std::endl;
	std::cout << "(3) - Find By Number (recursive)" << std::endl;
	std::cout << "(4) - Find By Number (iterative)" << std::endl;
	std::cout << "(5) - Quit" << std::endl << std::endl;
	while(true){
		readPhoneBook("phoneBook.txt", names, numbers);
		int choice = prompt();
		if (choice == 1){
			std::string name;
			std::cout << "Enter a name: ";
			std::getline(std::cin, name);
			int index = searchRecursive(names, name);
			if (index == -1){
				std::cout << std::endl << "That name does not exist in the phonebook." << std::endl;
			}
			else {
				std::cout << std::endl << index + 1 << ". " << names[index] << " - " << numbers[index] << std::endl;
			}
		}
		else if (choice == 2){
			std::string name = "";
			std::cout << "Enter a name: ";
			std::getline(std::cin, name);
			int index = searchIterative(names, name);
			if (index == -1){
				std::cout << std::endl << "That name does not exist in the phonebook." << std::endl;
			}
			else {
				std::cout << std::endl << index + 1 << ". " << names[index] << " - " << numbers[index] << std::endl;
			}
		}
		else if (choice == 3){
			std::string number = "";
			std::cout << "Enter a phone number: ";
			std::getline(std::cin, number);
			int index = searchRecursive(numbers, number);
			if (index == -1){
				std::cout << std::endl << "That number does not exist in the phonebook." << std::endl;
			}
			else {
				std::cout << std::endl << index + 1 << ". " << names[index] << " - " << numbers[index] << std::endl;
			}
		}
		else if (choice == 4){
			std::string number = "";
			std::cout << "Enter a phone number: ";
			std::getline(std::cin, number);
			int index = searchIterative(numbers, number);
			if (index == -1){
				std::cout << std::endl << "That number does not exist in the phonebook." << std::endl;
			}
			else {
				std::cout << std::endl << index + 1<< ". " << names[index] << " - " << numbers[index] << std::endl;
			}
		}
		else if (choice == 5){
			break;
		}
		std::cout << std::endl;
	}
}
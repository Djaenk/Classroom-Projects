#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

long long int stringToDecimal(std::string string) {
	reverse(string.begin(), string.end());
	long long int dec = 0;
	for (int i = 0; i < string.length(); i++) {
		long long int digit = string[i] - 48;
		for (int j = 0; j < i; j++) {
			digit *= 10;
		}
		dec += digit;
	}
	return dec;
}

long long int hexToDecimal(std::string hex) {
	reverse(hex.begin(), hex.end());
	long long int dec = 0;
	for (int i = 0; i < hex.length(); i++) {
		long long int digit = 0;
		if (isalpha(hex[i])) {
			switch (hex[i]) {
				case 'A':
					digit = 10;
					break;
				case 'B':
					digit = 11;
					break;
				case 'C':
					digit = 12;
					break;
				case 'D':
					digit = 13;
					break;
				case 'E':
					digit = 14;
					break;
				case 'F':
					digit = 15;
					break;
			}
		}
		else{
			digit = hex[i] - 48;
		}
		for (int j = 0; j < i; j++) {
			digit *= 16;
		}
		dec += digit;
	}
	return dec;
}

long long int binaryToDecimal(std::string binary) {
	reverse(binary.begin(), binary.end());
	long long int dec = 0;
	for (int i = 0; i < binary.length(); i++) {
		long long int digit;
		if (binary[i] == '1') {
			digit = 1;
		}
		if (binary[i] == '0') {
			digit = 0;	
		}
		for (int j = 0; j < i; j++) {
			digit *= 2;
		}
		dec += digit;
	}
	return dec;
}

std::string decimalToHex(long long int dec) {
	std::string hex = "";
	for (int i = 0;; i++) {
		std::string hex_digit = "";
		long long int digit = dec % 16;
		dec /= 16;
		if (digit > 9) {
			switch (digit) {
				case 10:
					hex_digit = "A";
					break;
				case 11:
					hex_digit = "B";
					break;
				case 12:
					hex_digit = "C";
					break;
				case 13:
					hex_digit = "D";
					break;
				case 14:
					hex_digit = "E";
					break;
				case 15:
					hex_digit = "F";
					break;
			}
		}
		else{
			hex_digit = std::to_string(digit);
		}
		hex += hex_digit;
		if (dec == 0) {
			break;
		}
	}
	reverse(hex.begin(), hex.end());
	return hex;
}

std::string decimalToBinary(long long int dec) {
	std::string binary = "";
	for (int i = 0;; i++){
		long long int digit = dec % 2;
		dec /= 2;
		binary += std::to_string(digit);
		if (dec == 0) {
			break;
		}
	}
}

int main() {
	std::ifstream input_file;
	std::string next_line;
	std::ofstream output_file;
	output_file.open("output.txt");
	std::cout << "Enter the name of the input file to be processed, enter nothing for default: ";
	std::string file_name;
	std::getline(std::cin, file_name);
	if (file_name.std::string::empty()) {
		input_file.std::ifstream::open("input.txt");	
		if (!input_file.is_open()) {
			std::cout << "Failed to open input file";
			return -1;
		}	
	}
	else {
		input_file.std::ifstream::open(file_name);
		if (!input_file.is_open()) {
			std::cout << "Failed to open input file";
			return -1;
		}
	}

	while (std::getline(input_file, next_line)) {
		char base;
		std::string num1;
		char operation;
		std::string num2;
		long long int operand1;
		long long int operand2;
		long long int result;
		std::istringstream input(next_line);
		
		if (isdigit(next_line[0])) {
			continue;
		}
		input >> base >> num1 >> operation >> num2;
		std::cout << std::endl << base << " " << num1 << " " << operation << " " << num2 << std::endl;
		switch (base) {
			case 'B':
				operand1 = binaryToDecimal(num1);
				operand2 = binaryToDecimal(num2);
				std::cout << result << std::endl;
				switch (operation) {
					case '+':
						result = operand1 + operand2;
						output_file << decimalToBinary(result) << std::endl;
						break;
					case '*':
						result = operand1 * operand2;
						output_file << decimalToBinary(result) << std::endl;
						break;
					default:
						output_file << "Invalid operation indicator." << std::endl;
				}
				std::cout << operand1 << " " << operation << " " << operand2 << std::endl;
				break;
			case 'D':
				operand1 = stringToDecimal(num1);
				operand2 = stringToDecimal(num2);
				switch (operation) {
					case '+':
						result = operand1 + operand2;
						output_file << operand1 + operand2 << std::endl;
						break;
					case '*':
						result = operand1 * operand2;
						output_file << operand1 * operand2 << std::endl;
						break;
					default:
						output_file << "Invalid operation indicator." << std::endl;
				}
				std::cout << operand1 << " " << operation << " " << operand2 << std::endl;
				break;
			case 'H':
				operand1 = hexToDecimal(num1);
				operand2 = hexToDecimal(num2);
				switch (operation) {
					case '+':
						result = operand1 + operand2;
						output_file << decimalToHex(result) << std::endl;
						break;
					case '*':
						result = operand1 * operand2;
						output_file << decimalToHex(result) << std::endl;
						break;
					default:
						output_file << "Invalid operation indicator." << std::endl;
				}
				std::cout << operand1 << " " << operation << " " << operand2 << std::endl;
				break;
			default:
				output_file << "Invalid numeral base system prefix." << std::endl;
		}
	}
	input_file.close();
	output_file.close();
	return 0;
}
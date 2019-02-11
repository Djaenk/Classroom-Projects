#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

long long int stringToDecimal(std::string string) {
	reverse(string.begin(), string.end());
	long long int dec = 0;
	for (int i = 0; i < string.length(); i++) {
		if (string[i] == '-') {
			dec *= -1;
			continue;
		}
		long long int digit = string[i] - 48;
		dec += digit * pow(10, i);
	}
	return dec;
}

long long int hexToDecimal(std::string hex) {
	reverse(hex.begin(), hex.end());
	std::string hex_table = "0123456789ABCDEF";
	long long int dec = 0;
	for (int i = 0; i < hex.length(); i++) {
		if (hex[i] == '-') {
			dec *= -1;
			continue;
		}
		int digit = hex_table.std::string::find(hex[i]); //stores position of first occurence of digit in hex table
		dec += digit * pow(16, i);
	}
	return dec;
}

long long int binaryToDecimal(std::string binary) {
	reverse(binary.begin(), binary.end());
	std::string binary_table = "01";
	long long int dec = 0;
	for (int i = 0; i < binary.length(); i++) {
		if (binary[i] == '-') {
			dec *= -1;
			continue;
		}
		int digit = binary_table.std::string::find(binary[i]); //stores position of first occurence of digit in binary table
		dec += digit * pow(2, i);
	}
	return dec;
}

std::string decimalToHex(long long int dec) {
	std::string hex = "";
	std::string hex_table = "0123456789ABCDEF";
	bool negative = false;
	if (dec < 0) {
		dec *= -1;
		negative = true;
	}
	do {
		int digit = dec % 16;
		dec /= 16;
		hex += hex_table[digit];
	} while (dec != 0);
	if (negative) {
		hex += '-';
	}
	reverse(hex.begin(), hex.end());
	return hex;
}

std::string decimalToBinary(long long int dec) {
	std::string binary = "";
	std::string binary_table = "01";
	bool negative = false;
	if (dec < 0) {
		dec *= -1;
		negative = true;
	}
	do {
		int digit = dec % 2;
		dec /= 2;
		binary += binary_table[digit];
	} while (dec != 0);
	if (negative) {
		binary += '-';
	}
	reverse(binary.begin(), binary.end());
	return binary;
}

int main() {
	std::ifstream input_file;
	std::ofstream output_file;
	output_file.open("output.txt");
	std::cout << "Enter the name of the input file to be processed, enter nothing for default: ";
	std::string file_name;
	std::getline(std::cin, file_name);

	//check if file opened
	if (file_name.empty()) {
		input_file.open("input.txt");	
	}
	else {
		input_file.open(file_name);
	}
	if (!input_file.is_open()) {
		std::cout << "Failed to open input file";
		return -1;
	}

	//perform arithmetic operations while file still has more lines
	while (input_file.peek() != EOF) {
		std::string base;
		std::string num1;
		std::string operation;
		std::string num2;
		long long int operand1;
		long long int operand2;
		long long int result;
		int counter;
		
		//I pretty much ignore the purpose of the first line in the input with this
		if (isdigit(input_file.peek())) {
			input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Number of lines processed:" << std::endl;
			continue;
		}
		else {
			input_file >> base >> num1 >> operation >> num2;
		}

		switch (base[0]) {
			case 'B':
				operand1 = binaryToDecimal(num1);
				operand2 = binaryToDecimal(num2);
				switch (operation[0]) {
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
				break;
			case 'D':
				operand1 = stringToDecimal(num1);
				operand2 = stringToDecimal(num2);
				switch (operation[0]) {
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
				break;
			case 'H':
				operand1 = hexToDecimal(num1);
				operand2 = hexToDecimal(num2);
				switch (operation[0]) {
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
				break;
			default:
				output_file << "Invalid numeral base system prefix." << std::endl;
		}
	counter++;
	std::cout << "\r" << counter;
	}
	input_file.close();
	output_file.close();
	return 0;
}
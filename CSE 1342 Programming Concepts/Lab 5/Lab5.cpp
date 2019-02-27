#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string>

int main () {
	std::string filename = "";
	std::cout << "enter filename" << std::endl;
	std::cin >> filename;
	while(filename != "unemp.txt"){
		std::cout << "error in file name, renter" << std::endl;
		std::cin >> filename;
	}
	std::ifstream unemployment_data;
	unemployment_data.open(filename);
	std::string headings;
	std::getline(unemployment_data, headings);
	while(unemployment_data.peek() != EOF){
		int year;
		long double data [12];
		unemployment_data >> year;
		for(int i = 0; i < 12; i++){
			unemployment_data >> data[i];
		}
		long double average = 0.0;
		for(int i = 0; i < 12; i++){
			average += data[i];
		}
		average /= 12.0;
		std::cout << "The average unemployment for year " << year << " is " << std::fixed << std::setprecision(2) << average << std::endl;
	}
}
#include <iostream>

using namespace std;

int main(){
	int scale;
	bool invalid_integer = true;
	while(invalid_integer){ //prompts user for input until valid input is recieved
		cout << "Input an integer in the range 5 to 20: ";
		cin >> scale;
		if(scale < 5 || scale > 20){
			cout << "Incorrect. The number is out of range." << endl;
		} else{
			invalid_integer = false;
		}
	}

	for(int i = 1; i <= scale; i++){ //loops over lines of figure
		for(int j = 1; j <= scale - i; j++){ //loops over the spaces of each line
			cout << " ";
		}
		for(int j = 1; j <= i; j++){ //loops over the astersks of each line
			cout << "*";
		}
		cout << endl;
	}
	return 0;
}
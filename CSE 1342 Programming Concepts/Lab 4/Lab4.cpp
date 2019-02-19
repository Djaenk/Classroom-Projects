#include <iostream>
#include <string>
using namespace std;

void reverseNumber(int); // function prototypes
bool isPalindrome(string,int,int);

int main()
{   int number;
    bool flag = true;
    string astring;
    cout << "enter a five digit number" << endl;
    cin >> number;
    reverseNumber(number);
    cout << endl;
    cout << "enter a string" << endl;
    cin >> astring;
    flag = isPalindrome(astring,0,astring.length()-1);
    if (flag)
       cout << astring << " is a palindrome " << endl;
    else
       cout << astring << " is not a palindrome " << endl;
    
}

void reverseNumber(int n)
{
	int digit = n % 10;
	n /= 10;
	cout << digit;
	if (n != 0){
		reverseNumber(n);
	}
}

bool isPalindrome(string theString,int x, int y)
{  
	if (x == y || x == y - 1){
		return true;
	}
	else if (theString[x] == theString[y]){
		return isPalindrome(theString, x + 1, y - 1);
	}
	else{
		return false;
	}
}

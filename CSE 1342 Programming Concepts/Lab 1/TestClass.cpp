/********************************************************
 * TestClass.cpp
 *
 * This file contains the implementation of the guessing game
 * 
 ********************************************************/


#include "TestClass.h"
#include <iostream>
using namespace std;
/***********************************************************
 * This is the implementation for the TestClass
 *
 ************************************************************/

void TestClass::getguess()
{

	cout << "I have a number between 1 and 100" << endl;
	cout << "Can you guess the number; Type your guess";
	cin >> guess;
}
bool TestClass::checkguess()
{
	if (guess == 56)
	{
		cout << "You are right" << endl;
		return true;
	}
	else
	{
		cout << "you are wrong" << endl;
		if (guess < 56)
			cout << "Your number is too low, try again\n";
		else
			cout << "Your number is too high, try again\n";
		return false;
	}
}


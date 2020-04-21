/***********************************************************
 * MainDriver.cpp
 *
 * This file is used for CSE 1342 - Lab 1. It will use the
 * TestClass class to create an object that
 * can play "guess a number" game 
 *
 ***********************************************************/

#include <iostream>
#include "TestClass.h"
using namespace std;

int main() {
	// create an object of type TestClass
	TestClass anObject;
	bool flag = false;
	while (flag == false){
		anObject.getguess();
		flag = anObject.checkguess();
	}
    cout << "Thanks for playing \n" << endl;
    return 0;
}


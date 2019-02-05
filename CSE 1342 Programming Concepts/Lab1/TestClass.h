/**********************************************************
 *
 * TestClass.h
 *
 * This file contains the interface for a TestClass that 
 * plays a "guess the number" game.
 * The implementation is found in TestClass.cpp.
 *
 ***********************************************************/



#ifndef Something
#define Something
class TestClass
{  private:
     int guess;
   public:
	 void getguess();
	 bool checkguess();
};
#endif

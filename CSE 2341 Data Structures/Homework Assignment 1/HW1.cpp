#include <iostream>
#include <cstring>

void overflow(int& count){
	std::cout << count << std::endl;
	overflow(++count);
}

class HW1
{
public:
   char *word;

   HW1() { }
   ~HW1() 
   { 
        delete [] word;
   }
};

void foo(HW1 a)
{
    //some operation here
}

int main(){
	// Question 1
	// int count = 0;
	// overflow(count);

	// Question 2
	// char data[6][10] = {"Sam", "Robert", "Mark", "Jason", "Alex", "Karen"};
	// std::cout << data[3] << std::endl; 
	// std::cout << *data[2] << std::endl; 
	// std::cout << *(*(data+1)+1) << std::endl;
	// // std::cout << ***data << std::endl;
	// std::cout << **(data+ 4) << std::endl; 
	// std::cout << *(data + 3) << std::endl;
	// std::cout << data << std::endl;

	// Question 3
	HW1 a;
    a.word = new char[80];
    strcpy(a.word, "abc");
    foo(a);
    return 0;
}
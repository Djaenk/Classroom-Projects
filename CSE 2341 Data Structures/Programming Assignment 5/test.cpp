#include "avltree.h"
#include "DocIndex.h"
#include "IndexInterface.h"
#include "porter2_stemmer.h"
#include "Parser.h"
#include "SearchEngine.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <experimental/filesystem>
#include <filesystem>
using namespace std::chrono;
using namespace std::experimental::filesystem;

int main(int argc, char *argv[]){
	auto start = high_resolution_clock::now();

	SearchEngine test;

	if(argc > 1){
		test.parseDirectory(argv[1]);
	}
	else{
	test.parseDirectory("./scotus-med");
	// test.parseDirectory("C:\\Users\\Anthony Wang\\Documents\\GitHub\\Classroom-Projects\\CSE 2341 Data Structures\\Programming Assignment 5\\scotus-med");
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count() << " microsecond parse time." << std::endl;
	
	test.wordQuery();

	return 0;
}
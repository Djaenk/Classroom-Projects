#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include "Classifier.hpp"
#include "DSlib/DSString.hpp"
#include "DSlib/DSVector.hpp"

TEST_CASE("Run through of DSVector functions"){
	DSVector<DSString> vector;

	SECTION("Ensure default constructor creates a vector with no elements"){
		REQUIRE(vector.len() == 0);
	}
	SECTION("Pushing objects expands the vector and makes the accessible through indexing"){
		DSString a = DSString("a");
		DSString b = DSString('b');
		vector.push_back(a);
		vector.push_back(b);
		vector.push_back(DSString("a"));
		vector.push_back(DSString('b'));

		REQUIRE(vector.len() == 4);
		REQUIRE(vector[0] == DSString("a"));
		REQUIRE(vector[1] == DSString('b'));
		REQUIRE(vector[0] == vector[2]);
		REQUIRE(vector[1] == vector[3]);
		REQUIRE(vector[2] == a);
		REQUIRE(vector[3] == b);
	}
	SECTION("Popping removes elements"){
		DSString a = DSString("a");
		DSString b = DSString('b');
		vector.push_back(a);
		vector.push_back(b);
		vector.push_back(DSString("a"));
		vector.push_back(DSString('b'));

		vector.pop_back();
		REQUIRE(vector.len() == 3);

		vector.pop_back();
		REQUIRE(vector.len() == 2);
	}
	SECTION("Inserting and erasing adds or removes elements not at the end of the vector"){
		DSString a = DSString("a");
		DSString b = DSString('b');
		vector.push_back(a);
		vector.push_back(b);

		vector.insert(1, DSString("c"));
		REQUIRE(vector.len() == 3);
		REQUIRE(vector[1] == DSString("c"));

		vector.erase(1);
		REQUIRE(vector.len() == 2);
		REQUIRE(vector[1] == DSString("b"));
	}
	SECTION("The back function should return the last element of the vector"){
		DSString a = DSString("a");
		DSString b = DSString('b');
		vector.push_back(a);
		vector.push_back(b);

		vector.insert(1, DSString("c"));
		vector.insert(1, DSString("c"));
		REQUIRE(vector.back() == vector[3]);
		REQUIRE(vector.back() == DSString("b"));
	}
}

int main(int argc, char *argv[]){
	if(argc == 1){
		int result = Catch::Session().run();
	}
	if(argc == 6){
	TweetClassifier classifier;
	std::ifstream input(argv[1]);
	std::ifstream target(argv[2]);
	classifier.train(input, target);
	input = std::ifstream(argv[3]);
	target = std::ifstream(argv[4]);
	classifier.test(input, target, argv[5]);
	}
}
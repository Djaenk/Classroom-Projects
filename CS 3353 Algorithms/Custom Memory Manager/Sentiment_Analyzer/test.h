#include <iostream>
#include <fstream>
#include "Classifier.hpp"

// int main(int argc, char *argv[]){
// 	if(argc == 1){
// 		int result = Catch::Session().run();
// 	}
// 	if(argc == 6){
// 	TweetClassifier classifier;
// 	std::ifstream input(argv[1]);
// 	std::ifstream target(argv[2]);
// 	classifier.train(input, target);
// 	input = std::ifstream(argv[3]);
// 	target = std::ifstream(argv[4]);
// 	classifier.test(input, target, argv[5]);
// 	}
// }
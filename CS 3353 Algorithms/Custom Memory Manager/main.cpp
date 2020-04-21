#include "manager.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#include "Sentiment_Analyzer/test.h"

//if boolean uniform is false, allocations will be of random size up to uint allocation_size
int64_t allocation_test(uint allocation_count, uint allocation_size, bool uniform, bool sequential){
	char* pointers[allocation_count] = {nullptr};
	auto start = std::chrono::high_resolution_clock::now();
	if(uniform && sequential){
		for(uint i = 0; i < allocation_count; ++i){
			pointers[i] = new char[allocation_size];
		}
		for(uint i = 0; i < allocation_count; ++i){
			delete pointers[i];
		}
	}
	else if(!uniform && sequential){
		for(uint i = 0; i < allocation_count; ++i){
			pointers[i] = new char[rand() % (2 * allocation_size) + 1];
		}
		for(uint i = 0; i < allocation_count; ++i){
			delete pointers[i];
		}
	}
	else if(uniform && !sequential){
		for(uint i = 0; i < allocation_count; ++i){
			if(rand() % 2){
				pointers[i] = new char[allocation_size];
			}
		}
		for(uint i = 0; i < allocation_count; ++i){
			if(pointers[i] == nullptr){
				pointers[i] = new char[allocation_size];
			}
			else{
				delete pointers[i];
				pointers[i] = nullptr;
			}
		}
		for(uint i = 0; i < allocation_count; ++i){
			delete pointers[i];
		}
	}
	else if(!uniform && !sequential){
		for(uint i = 0; i < allocation_count; ++i){
			if(rand() % 2){
				pointers[i] = new char[rand() % (2 * allocation_size - 2) + 1];
			}
		}
		for(uint i = 0; i < allocation_count; ++i){
			if(pointers[i] == nullptr){
				pointers[i] = new char[rand() % (2 * allocation_size - 2) + 1];
			}
			else{
				delete pointers[i];
				pointers[i] = nullptr;
			}
		}
		for(uint i = 0; i < allocation_count; ++i){
			delete pointers[i];
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
}

int64_t sentiment_test(uint size){
	auto start = std::chrono::high_resolution_clock::now();
	
	TweetClassifier classifier;
	std::ifstream input("train_data.csv");
	std::ifstream target("train_target.csv");
	classifier.train(input, target, size);
	input = std::ifstream("test_data.csv");
	target = std::ifstream("test_target.csv");
	classifier.test(input, target, "test_output.txt", size);

	auto stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
}

int main(int argc, char *argv[]){
	char fit;
	if(argc > 1)
		fit = argv[1][1];
	else
		fit = 'd';
	
	AllocatorSingleton::setFit(fit);
	std::string output_filename = "test-results-.csv";
	output_filename.insert(13, 1, fit);
	std::ofstream output(output_filename);

	output << "Synthetic Stress Testing" << std::endl;
	output << "count,size,uniform,sequential,duration(nanoseconds)" << std::endl;
	uint count,size;
	for(uint i = 0; i <= 13; ++i){
		count = pow(2, i); 
		for(uint j = 1; j <= 15; ++j){
			size = pow(2, j);
			output << count << ',' << size << ",yes,yes," << allocation_test(count, size, true, true) << std::endl;
			output << count << ',' << size << ",yes,no," << allocation_test(count, size, true, false) << std::endl;
			output << count << ',' << size << ",no,yes," << allocation_test(count, size, false, true) << std::endl;
			output << count << ',' << size << ",no,no," << allocation_test(count, size, false, false) << std::endl;
		}
	}

	output << "Sentiment Analyzer Stress Testing" << std::endl;
	output << "tweet count,duration(nanoseconds)" << std::endl;
	for(uint i = 10; i <= 80; i += 10){
		if(fit == 'c' && i > 40){
			break;
		}
		output << i << ',' << sentiment_test(i) << std::endl;
	}
	output << std::endl;
}
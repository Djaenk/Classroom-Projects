#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <utility>

enum State {S0, S1, S2, S3, S4, S3_S4, END};
std::unordered_map<std::string, std::pair<int, int>> FSMTable = {
	{"the", std::make_pair(State::S0, State::S1)},
	{"lazy", std::make_pair(State::S1, State::S1)},
	{"smelly", std::make_pair(State::S1, State::S1)},
	{"dog", std::make_pair(State::S1, State::S2)},
	{"cat", std::make_pair(State::S1, State::S2)},
	{"ate", std::make_pair(State::S2, State::S3)},
	{"ran", std::make_pair(State::S2, State::S3)},
	{"slowly", std::make_pair(State::S3, State::S4)},
	{"noisily", std::make_pair(State::S3, State::S4)},
	{"EOI", std::make_pair(State::S3_S4, State::END)},
};

bool runFSM(std::string sentence){
	std::istringstream words(sentence);
	std::string word;
	int state = State::S0;
	while (words){
		words >> word;
		if (!words) word = "EOI";

		if (FSMTable[word].first == state)
			state = FSMTable[word].second;
		else if (FSMTable[word].first == State::S3_S4
		&& (state == State::S3 || state == State::S4))
			state = FSMTable[word].second;
		else
			return false;
	}
	return state == State::END;
}

std::unordered_map<std::string, bool> unitTests = {
	{"the", false},
	{"the lazy smelly dog ate slowly", true},
	{"the cat ran noisily", true},
	{"the cat", false},
	{"smelly dog ran slowly", false},
	{"the dog ate", true}
};

void runFSMTests(){
	for (const auto& test : unitTests){
		if (runFSM(test.first) == test.second)
			std::cout << "Test passed" << std::endl;
		else
			std::cout << "Test failed" << std::endl;
	}
}

int main(){
	runFSMTests();
}
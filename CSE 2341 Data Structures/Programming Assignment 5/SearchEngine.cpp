#include "SearchEngine.h"

using namespace std::experimental;

void SearchEngine::parseDirectory(const std::string directory_path){
	for(filesystem::path path : filesystem::directory_iterator(directory_path)){
		if(path.extension() == ".json"){
			std::ifstream file(path);
			if(file){
				parser.indexDocument(file, index);
			}
		}
	}
}

void SearchEngine::wordQuery(){
	std::string query = "";
	do{
		std::cout << "Enter word to be queried: ";
		std::cin >> query;
		std::cout << query << " stems to ";
		Porter2Stemmer::trim(query);
		Porter2Stemmer::stem(query);
		std::cout << query << " and has a total relevant frequency of " << index[query].total_frequency()
			<< " among " << index[query].doc_indices.size() << " documents.\n" << std::endl;
	}while(query.compare("") != 0);
}

DocIndex& SearchEngine::getWord(const std::string word){
	return index[word];
}

DocIndex& SearchEngine::getWord(const char* word){
	return index[std::string(word)];
}